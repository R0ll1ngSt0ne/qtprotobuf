// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: globalenumssamenamespace.proto

#ifndef PROTOBUF_INCLUDED_globalenumssamenamespace_2eproto
#define PROTOBUF_INCLUDED_globalenumssamenamespace_2eproto

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3006001
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3006001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/generated_enum_reflection.h>
// @@protoc_insertion_point(includes)
#define PROTOBUF_INTERNAL_EXPORT_protobuf_globalenumssamenamespace_2eproto 

namespace protobuf_globalenumssamenamespace_2eproto {
// Internal implementation detail -- do not use these members.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[1];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors();
}  // namespace protobuf_globalenumssamenamespace_2eproto
namespace qtprotobufnamespace {
namespace tests {
}  // namespace tests
}  // namespace qtprotobufnamespace
namespace qtprotobufnamespace {
namespace tests {

enum TestEnum2 {
  TEST_ENUM2_VALUE0 = 0,
  TEST_ENUM2_VALUE1 = 1,
  TEST_ENUM2_VALUE2 = 2,
  TEST_ENUM2_VALUE3 = 4,
  TEST_ENUM2_VALUE4 = 3,
  TestEnum2_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  TestEnum2_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool TestEnum2_IsValid(int value);
const TestEnum2 TestEnum2_MIN = TEST_ENUM2_VALUE0;
const TestEnum2 TestEnum2_MAX = TEST_ENUM2_VALUE3;
const int TestEnum2_ARRAYSIZE = TestEnum2_MAX + 1;

const ::google::protobuf::EnumDescriptor* TestEnum2_descriptor();
inline const ::std::string& TestEnum2_Name(TestEnum2 value) {
  return ::google::protobuf::internal::NameOfEnum(
    TestEnum2_descriptor(), value);
}
inline bool TestEnum2_Parse(
    const ::std::string& name, TestEnum2* value) {
  return ::google::protobuf::internal::ParseNamedEnum<TestEnum2>(
    TestEnum2_descriptor(), name, value);
}
// ===================================================================


// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace tests
}  // namespace qtprotobufnamespace

namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::qtprotobufnamespace::tests::TestEnum2> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::qtprotobufnamespace::tests::TestEnum2>() {
  return ::qtprotobufnamespace::tests::TestEnum2_descriptor();
}

}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_INCLUDED_globalenumssamenamespace_2eproto
