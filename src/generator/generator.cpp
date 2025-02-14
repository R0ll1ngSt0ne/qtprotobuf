/*
 * MIT License
 *
 * Copyright (c) 2019 Alexey Edelev <semlanik@gmail.com>
 *
 * This file is part of QtProtobuf project https://git.semlanik.org/semlanik/qtprotobuf
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this
 * software and associated documentation files (the "Software"), to deal in the Software
 * without restriction, including without limitation the rights to use, copy, modify,
 * merge, publish, distribute, sublicense, and/or sell copies of the Software, and
 * to permit persons to whom the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies
 * or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
 * FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include "generator.h"
#include "templates.h"
#include "classgeneratorbase.h"
#include "protobufclassgenerator.h"
#include "protobufsourcegenerator.h"
#include "globalenumsgenerator.h"
#include "globalenumssourcegenerator.h"
#include "servergenerator.h"
#include "clientgenerator.h"
#include "clientsourcegenerator.h"
#include "utils.h"

#include <iostream>
#include <google/protobuf/stubs/logging.h>
#include <google/protobuf/stubs/common.h>
#include <google/protobuf/io/printer.h>
#include <google/protobuf/io/zero_copy_stream.h>
#include <google/protobuf/descriptor.h>

using namespace ::QtProtobuf::generator;
using namespace ::google::protobuf;
using namespace ::google::protobuf::compiler;

bool QtGenerator::Generate(const FileDescriptor *file,
                           const std::string &parameter,
                           GeneratorContext *generatorContext,
                           std::string *error) const
{
    // the variable contains only the relative path to ouput dir which is unused in this method
    UNUSED(parameter);

    if (file->syntax() != FileDescriptor::SYNTAX_PROTO3) {
        *error = "Invalid proto used. This plugin only supports 'proto3' syntax";
        return false;
    }

    for (int i = 0; i < file->message_type_count(); i++) {
        const Descriptor *message = file->message_type(i);

        //Detect nested fields and filter maps fields
        int mapsFieldsCount = 0;
        for (int j = 0; j < message->nested_type_count(); j++) {
            for (int k = 0; k < message->field_count(); k++) {
                if (message->field(k)->is_map() && message->field(k)->message_type() == message->nested_type(j)) {
                    ++mapsFieldsCount;
                }
            }
        }

        if (message->nested_type_count() > 0 && message->nested_type_count() > mapsFieldsCount) {
            std::cerr << file->name() << ":" << (message->index() + 1) << ": " << " Error: Meta object features not supported for nested classes in " << message->full_name() << std::endl;
            continue;
        }
        std::string baseFilename(message->name());
        utils::tolower(baseFilename);

        std::string filename = baseFilename + ".h";
        ProtobufClassGenerator classGen(message,
                                        std::move(std::unique_ptr<io::ZeroCopyOutputStream>(generatorContext->Open(filename))));
        classGen.run();

        filename = baseFilename + ".cpp";
            ProtobufSourceGenerator classSourceGen(message,
                                      std::move(std::unique_ptr<io::ZeroCopyOutputStream>(generatorContext->Open(filename))));
            classSourceGen.run();
    }

    for (int i = 0; i < file->service_count(); i++) {
        const ServiceDescriptor *service = file->service(i);
        std::string baseFilename(service->name());
        utils::tolower(baseFilename);

        std::string fullFilename = baseFilename + "server.h";
        ServerGenerator serverGen(service,
                                  std::move(std::unique_ptr<io::ZeroCopyOutputStream>(generatorContext->Open(fullFilename))));
        serverGen.run();

        fullFilename = baseFilename + "client.h";
        ClientGenerator clientGen(service,
                                  std::move(std::unique_ptr<io::ZeroCopyOutputStream>(generatorContext->Open(fullFilename))));
        clientGen.run();

        fullFilename = baseFilename + "client.cpp";
        ClientSourceGenerator clientSrcGen(service,
                                           std::move(std::unique_ptr<io::ZeroCopyOutputStream>(generatorContext->Open(fullFilename))));
        clientSrcGen.run();
    }
    return true;
}

bool QtGenerator::GenerateAll(const std::vector<const FileDescriptor *> &files, const string &parameter, GeneratorContext *generatorContext, string *error) const
{
    std::string globalEnumsFilename = "globalenums";

    PackagesList packageList;
    for (auto file : files) {
        packageList[file->package()].push_back(file);
    }

    GlobalEnumsGenerator enumGen(packageList,
                                 std::move(std::unique_ptr<io::ZeroCopyOutputStream>(generatorContext->Open(globalEnumsFilename + ".h"))));
    enumGen.run();

    GlobalEnumsSourceGenerator enumSourceGen(packageList,
                                             std::move(std::unique_ptr<io::ZeroCopyOutputStream>(generatorContext->Open(globalEnumsFilename + ".cpp"))));
    enumSourceGen.run();
    return CodeGenerator::GenerateAll(files, parameter, generatorContext, error);

}

