/*
 * MIT License
 *
 * Copyright (c) 2019 Alexey Edelev <semlanik@gmail.com>, Tatyana Borisova <tanusshhka@mail.ru>
 *
 * This file is part of qtprotobuf project https://git.semlanik.org/semlanik/qtprotobuf
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

#include "templates.h"

using namespace qtprotobuf::generator;

const char *Templates::DefaultProtobufIncludesTemplate = "#include <QMetaType>\n"
                                                         "#include <QList>\n"
                                                         "#include <QtQml/QQmlListProperty>\n"
                                                         "#include <qprotobufobject.h>\n"
                                                         "#include <unordered_map>\n"
                                                         "#include <QSharedPointer>\n\n";

const char *Templates::GlobalEnumClassNameTemplate = "GlobalEnums";

const char *Templates::DisclaimerTemplate = "/* This file is autogenerated. DO NOT CHANGE. All changes will be lost */\n\n";
const char *Templates::PreambleTemplate = "#pragma once\n\n"
                                      "#include <QObject>\n";

const char *Templates::InternalIncludeTemplate =  "#include \"$include$.h\"\n";
const char *Templates::ExternalIncludeTemplate = "#include <$include$>\n";
const char *Templates::GlobalEnumIncludeTemplate = "#include <globalenums.h>\n";

const char *Templates::UsingQtProtobufNamespaceTemplate = "\nusing namespace qtprotobuf;\n";
const char *Templates::ComplexTypeRegistrationMethodTemplate = "static void registerTypes();\n";
const char *Templates::ComplexTypeRegistrationTemplate = "void $classname$::registerTypes()\n{\n"
                                                         "    static bool registationDone = false;\n"
                                                         "    if (!registationDone) {\n"
                                                         "        registationDone = true;\n"
                                                         "        qRegisterMetaType<$classname$>(\"$classname$\");\n"
                                                         "        qRegisterMetaType<$classname$List>(\"$classname$List\");\n"
                                                         "        qRegisterMetaType<$classname$>(\"$namespaces$::$classname$\");\n"
                                                         "        qRegisterMetaType<$classname$List>(\"$namespaces$::$classname$List\");\n"
                                                         "";
const char *Templates::ComplexGlobalEnumRegistrationTemplate = "void $classname$::registerTypes()\n{\n"
                                                               "    static bool registationDone = false;\n"
                                                               "    if (!registationDone) {\n"
                                                               "        registationDone = true;\n";
const char *Templates::ComplexGlobalEnumFieldRegistrationTemplate = "qRegisterMetaType<$classname$::$enum$>(\"$namespaces$::$classname$::$enum$\");\n";
const char *Templates::ComplexListTypeUsingTemplate = "using $classname$List = QList<QSharedPointer<$classname$>>;\n";
const char *Templates::MapTypeUsingTemplate = "using $classname$ = QMap<$key$, $value$>;\n";
const char *Templates::MessageMapTypeUsingTemplate = "using $classname$ = QMap<$key$, QSharedPointer<$value$>>;\n";

const char *Templates::EnumTypeUsingTemplate = "using $enum$List = QList<$enum$>;\n";

const char *Templates::NamespaceTemplate = "\nnamespace $namespace$ {\n";
const char *Templates::UsingNamespaceTemplate = "using namespace $namespace$;\n";
const char *Templates::NonProtoClassDefinitionTemplate = "\nclass $classname$ : public QObject\n"
                                                         "{\n"
                                                         "    Q_OBJECT\n";
const char *Templates::ProtoClassDefinitionTemplate = "\nclass $classname$ : public QObject\n"
                                                 "{\n"
                                                 "    Q_OBJECT\n";

const char *Templates::PropertyTemplate = "Q_PROPERTY($type$ $property_name$ READ $property_name$ WRITE set$property_name_cap$ NOTIFY $property_name$Changed)\n";
const char *Templates::MessagePropertyTemplate = "Q_PROPERTY($type$ *$property_name$ READ $property_name$_p WRITE set$property_name_cap$_p NOTIFY $property_name$Changed)\n";
const char *Templates::QmlListPropertyTemplate = "Q_PROPERTY(QQmlListProperty<$type_nolist$> $property_name$Data READ $property_name$_l NOTIFY $property_name$Changed)\n";

const char *Templates::MemberTemplate = "$type$ m_$property_name$;\n";
const char *Templates::EnumMemberTemplate = "::$type$ m_$property_name$;\n";
const char *Templates::PublicBlockTemplate = "\npublic:\n";
const char *Templates::PrivateBlockTemplate = "\nprivate:\n";
const char *Templates::EnumDefinitionTemplate = "enum $enum$ {\n";
const char *Templates::EnumFieldTemplate = "$enumvalue$ = $value$,\n";
const char *Templates::ProtoConstructorTemplate = "$classname$($parameter_list$QObject *parent = nullptr) : QObject(parent)";
const char *Templates::ConstructorTemplate = "$classname$();\n";
const char *Templates::ConstructorHeaderTemplate = "$classname$(){}\n";
const char *Templates::CopyConstructorTemplate = "$classname$(const $classname$ &other) : QObject() {\n";
const char *Templates::MoveConstructorTemplate = "$classname$($classname$ &&other) : QObject() {\n";
const char *Templates::CopyFieldTemplate = "m_$property_name$ = other.m_$property_name$;\n";
const char *Templates::MoveComplexFieldTemplate = "m_$property_name$ = std::move(other.m_$property_name$);\n";
const char *Templates::MoveFieldTemplate = "m_$property_name$ = std::exchange(other.m_$property_name$, 0);\n";
const char *Templates::EnumMoveFieldTemplate = "m_$property_name$ = other.m_$property_name$;\n";
const char *Templates::AssignmentOperatorTemplate = "$classname$ &operator =(const $classname$ &other) {\n";
const char *Templates::AssignmentOperatorReturnTemplate = "return *this;\n";
const char *Templates::MoveAssignmentOperatorTemplate = "$classname$ &operator =($classname$ &&other) {\n";
const char *Templates::EqualOperatorTemplate = "bool operator ==(const $type$ &other) const {\n"
                                               "    return ";
const char *Templates::EqualOperatorPropertyTemplate = "m_$property_name$ == other.m_$property_name$";
const char *Templates::NotEqualOperatorTemplate = "bool operator !=(const $type$ &other) const {\n"
                                                  "    return !this->operator ==(other);\n"
                                                  "}\n\n";

const char *Templates::GetterMessageTemplate = "$type$ *$property_name$_p() const {\n" //formally const...
                                        "    return const_cast<$type$*>(&m_$property_name$);\n"
                                        "}\n\n";

const char *Templates::GetterTemplate = "$type$ $property_name$() const {\n"
                                        "    return m_$property_name$;\n"
                                        "}\n\n";

const char *Templates::GetterContainerExtraTemplate = "$type$ &$property_name$() {\n"
                                        "    return m_$property_name$;\n"
                                        "}\n\n";

const char *Templates::QmlListGetterTemplate = "QQmlListProperty<$type_nolist$> $property_name$_l() {\n"
                                               "    return qtprotobuf::ProtobufObjectPrivate::constructQmlListProperty<$type_nolist$>(this, &m_$property_name$);\n"
                                               "}\n\n";

const char *Templates::SetterTemplateMessageType = "void set$property_name_cap$_p($type$ *$property_name$) {\n"
                                                   "    if ($property_name$ == nullptr) {\n"
                                                   "        m_$property_name$ = {};\n"
                                                   "    }\n"
                                                   "    if (m_$property_name$ != *$property_name$) {\n"
                                                   "        m_$property_name$ = *$property_name$;\n"
                                                   "        $property_name$Changed();\n"
                                                   "    }\n"
                                                   "    //NOTE: take ownership of value\n"
                                                   "    delete $property_name$;\n"
                                                   "}\n\n";

const char *Templates::SetterTemplateComplexType = "void set$property_name_cap$(const $type$ &$property_name$) {\n"
                                                   "    if (m_$property_name$ != $property_name$) {\n"
                                                   "        m_$property_name$ = $property_name$;\n"
                                                   "        $property_name$Changed();\n"
                                                   "    }\n"
                                                   "}\n\n";

const char *Templates::SetterTemplateSimpleType = "void set$property_name_cap$(const $type$ &$property_name$) {\n"
                                                   "    if (m_$property_name$ != $property_name$) {\n"
                                                   "        m_$property_name$ = $property_name$;\n"
                                                   "        $property_name$Changed();\n"
                                                   "    }\n"
                                                   "}\n\n";

const char *Templates::SignalsBlockTemplate = "\nsignals:\n";
const char *Templates::SignalTemplate = "void $property_name$Changed();\n";

const char *Templates::FieldsOrderingDefinitionContainerTemplate = "static const std::unordered_map<int/*field number*/, int/*property number*/> propertyOrdering;\n";

const char *Templates::FieldsOrderingContainerTemplate = "const std::unordered_map<int, int> $type$::propertyOrdering = {";
const char *Templates::FieldOrderTemplate = "{$field_number$,$property_number$}";

const char *Templates::EnumTemplate = "$type$";

const char *Templates::SimpleBlockEnclosureTemplate = "}\n\n";
const char *Templates::SemicolonBlockEnclosureTemplate = "};\n";
const char *Templates::EmptyBlockTemplate = "{}\n\n";
const char *Templates::PropertyInitializerTemplate = "\n    ,m_$property_name$($property_name$)";
const char *Templates::ConstructorContentTemplate = "\n{\n    registerTypes();\n}\n";

const char *Templates::DeclareMetaTypeTemplate = "Q_DECLARE_METATYPE($namespaces$::$classname$)\n";
const char *Templates::DeclareMetaTypeListTemplate = "Q_DECLARE_METATYPE($namespaces$::$classname$List)\n";
const char *Templates::DeclareMessageMetaTypeTemplate = "Q_DECLARE_METATYPE($namespaces$::$classname$)\n"
                                                        "Q_DECLARE_OPAQUE_POINTER($namespaces$::$classname$)\n";

const char *Templates::DeclareComplexListTypeTemplate = "Q_DECLARE_METATYPE($namespaces$::$classname$List)\n"
                                                        "Q_DECLARE_METATYPE(QQmlListProperty<$namespaces$::$classname$>)\n";
const char *Templates::RegisterMetaTypeDefaultTemplate = "qRegisterMetaType<$namespaces$::$type$>();\n";
const char *Templates::RegisterMetaTypeTemplateNoNamespace = "qRegisterMetaType<$namespaces$::$type$>(\"$type$\");\n";
const char *Templates::RegisterMetaTypeTemplate = "qRegisterMetaType<$namespaces$::$type$>(\"$namespaces$::$type$\");\n";
const char *Templates::RegisterQmlListPropertyMetaTypeTemplate = "qRegisterMetaType<QQmlListProperty<$namespaces$::$classname$>>(\"QQmlListProperty<$namespaces$::$classname$>\");\n"
                                                                 "qRegisterMetaType<QQmlListProperty<$namespaces$::$classname$>>(\"QQmlListProperty<$classname$>\");\n";


const char *Templates::QEnumTemplate = "Q_ENUM($type$)\n";

const char *Templates::MapSerializationRegisterTemplate = "qtprotobuf::ProtobufObjectPrivate::wrapSerializer<$classname$::$type$>(\n"
                                                          "qtprotobuf::ProtobufObjectPrivate::serializeMap<$key_type$, $value_type$>,\n"
                                                          "qtprotobuf::ProtobufObjectPrivate::deserializeMap<$key_type$, $value_type$>\n"
                                                          ", qtprotobuf::LengthDelimited);\n";

const char *Templates::ClassDefinitionTemplate = "\nclass $classname$ : public $parent_class$\n"
                                                 "{\n";
const char *Templates::ClientMethodDeclarationSyncTemplate = "Q_INVOKABLE bool $method_name$(const $param_type$ &$param_name$, $return_type$ &$return_name$);\n";
const char *Templates::ClientMethodDeclarationAsyncTemplate = "Q_INVOKABLE bool $method_name$(const $param_type$ &$param_name$, const qtprotobuf::AsyncReply<$return_type$> &reply);\n";
const char *Templates::ServerMethodDeclarationTemplate = "Q_INVOKABLE virtual $return_type$ $method_name$(const $param_type$ &$param_name$) = 0;\n";


const char *Templates::ConstructorDefinitionSyncTemplate = "\n$classname$::$classname$() : $parent_class$(\"$service_name$\")\n"
                                                           "{\n"
                                                           "}\n";
const char *Templates::ClientMethodDefinitionSyncTemplate = "\nbool $classname$::$method_name$(const $param_type$ &$param_name$, $return_type$ &$return_name$)\n"
                                                            "{\n"
                                                            "    return call(\"$method_name$\", $param_name$, $return_name$);\n"
                                                            "}\n";
const char *Templates::ClientMethodDefinitionAsyncTemplate = "\nbool $classname$::$method_name$(const $param_type$ &$param_name$, const qtprotobuf::AsyncReply<$return_type$> &reply)\n"
                                                             "{\n"
                                                             "    //TODO: call transport method to serialize this method\n"
                                                             "    return false;\n"
                                                             "}\n";
const char *Templates::SerializersTemplate = "Q_DECLARE_PROTOBUF_SERIALIZERS($classname$)\n";
const char *Templates::RegisterSerializersTemplate = "qtprotobuf::ProtobufObjectPrivate::registerSerializers<$classname$>();\n";
const char *Templates::QmlRegisterTypeTemplate = "qmlRegisterType<$namespaces$::$classname$>(\"$package$\", 1, 0, \"$classname$\");\n";
const char *Templates::QmlRegisterTypeUncreatableTemplate = "qmlRegisterUncreatableType<$namespaces$::$classname$>(\"$package$\", 1, 0, \"$classname$\", \"$namespaces$::$classname$ Could not be created from qml context\");\n";

const std::unordered_map<::google::protobuf::FieldDescriptor::Type, std::string> Templates::TypeReflection = {
    {::google::protobuf::FieldDescriptor::TYPE_DOUBLE, "double"},
    {::google::protobuf::FieldDescriptor::TYPE_FLOAT, "float"},
    {::google::protobuf::FieldDescriptor::TYPE_INT64, "int64"},     //Limited usage see https://doc.qt.io/qt-5/qtqml-typesystem-basictypes.html
    {::google::protobuf::FieldDescriptor::TYPE_UINT64,"uint64"},    //Limited usage see https://doc.qt.io/qt-5/qtqml-typesystem-basictypes.html
    {::google::protobuf::FieldDescriptor::TYPE_INT32, "int32"},
    {::google::protobuf::FieldDescriptor::TYPE_FIXED64, "fixed64"},  //Limited usage see https://doc.qt.io/qt-5/qtqml-typesystem-basictypes.html
    {::google::protobuf::FieldDescriptor::TYPE_FIXED32, "fixed32"},
    {::google::protobuf::FieldDescriptor::TYPE_BOOL, "bool"},
    {::google::protobuf::FieldDescriptor::TYPE_STRING, "QString"},
    {::google::protobuf::FieldDescriptor::TYPE_BYTES, "QByteArray"},
    {::google::protobuf::FieldDescriptor::TYPE_UINT32, "uint32"},    //Limited usage see https://doc.qt.io/qt-5/qtqml-typesystem-basictypes.html
    {::google::protobuf::FieldDescriptor::TYPE_SFIXED32, "sfixed32"},
    {::google::protobuf::FieldDescriptor::TYPE_SFIXED64, "sfixed64"}, //Limited usage see https://doc.qt.io/qt-5/qtqml-typesystem-basictypes.html
    {::google::protobuf::FieldDescriptor::TYPE_SINT32, "sint32"},
    {::google::protobuf::FieldDescriptor::TYPE_SINT64, "sint64"}     //Limited usage see https://doc.qt.io/qt-5/qtqml-typesystem-basictypes.html
};
