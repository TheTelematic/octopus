// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: protobuf/topic.proto

#undef CHECK

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "topic.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace octopus {
class GenericTopicDefaultTypeInternal : public ::google::protobuf::internal::ExplicitlyConstructed<GenericTopic> {
} _GenericTopic_default_instance_;

namespace protobuf_protobuf_2ftopic_2eproto {


namespace {

::google::protobuf::Metadata file_level_metadata[1];

}  // namespace

PROTOBUF_CONSTEXPR_VAR ::google::protobuf::internal::ParseTableField
    const TableStruct::entries[] = {
  {0, 0, 0, ::google::protobuf::internal::kInvalidMask, 0, 0},
};

PROTOBUF_CONSTEXPR_VAR ::google::protobuf::internal::AuxillaryParseTableField
    const TableStruct::aux[] = {
  ::google::protobuf::internal::AuxillaryParseTableField(),
};
PROTOBUF_CONSTEXPR_VAR ::google::protobuf::internal::ParseTable const
    TableStruct::schema[] = {
  { NULL, NULL, 0, -1, -1, false },
};

const ::google::protobuf::uint32 TableStruct::offsets[] = {
  ~0u,  // no _has_bits_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GenericTopic, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GenericTopic, msg_),
};

static const ::google::protobuf::internal::MigrationSchema schemas[] = {
  { 0, -1, sizeof(GenericTopic)},
};

static ::google::protobuf::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::google::protobuf::Message*>(&_GenericTopic_default_instance_),
};

namespace {

void protobuf_AssignDescriptors() {
  AddDescriptors();
  ::google::protobuf::MessageFactory* factory = NULL;
  AssignDescriptors(
      "protobuf/topic.proto", schemas, file_default_instances, TableStruct::offsets, factory,
      file_level_metadata, NULL, NULL);
}

void protobuf_AssignDescriptorsOnce() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &protobuf_AssignDescriptors);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::internal::RegisterAllTypes(file_level_metadata, 1);
}

}  // namespace

void TableStruct::Shutdown() {
  _GenericTopic_default_instance_.Shutdown();
  delete file_level_metadata[0].reflection;
}

void TableStruct::InitDefaultsImpl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::internal::InitProtobufDefaults();
  _GenericTopic_default_instance_.DefaultConstruct();
}

void InitDefaults() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &TableStruct::InitDefaultsImpl);
}
void AddDescriptorsImpl() {
  InitDefaults();
  static const char descriptor[] = {
      "\n\024protobuf/topic.proto\022\007octopus\"\033\n\014Gener"
      "icTopic\022\013\n\003msg\030\001 \001(\tb\006proto3"
  };
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
      descriptor, 68);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "protobuf/topic.proto", &protobuf_RegisterTypes);
  ::google::protobuf::internal::OnShutdown(&TableStruct::Shutdown);
}

void AddDescriptors() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &AddDescriptorsImpl);
}
// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer {
  StaticDescriptorInitializer() {
    AddDescriptors();
  }
} static_descriptor_initializer;

}  // namespace protobuf_protobuf_2ftopic_2eproto


// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int GenericTopic::kMsgFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

GenericTopic::GenericTopic()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (GOOGLE_PREDICT_TRUE(this != internal_default_instance())) {
    protobuf_protobuf_2ftopic_2eproto::InitDefaults();
  }
  SharedCtor();
  // @@protoc_insertion_point(constructor:octopus.GenericTopic)
}
GenericTopic::GenericTopic(const GenericTopic& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL),
      _cached_size_(0) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  msg_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (from.msg().size() > 0) {
    msg_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.msg_);
  }
  // @@protoc_insertion_point(copy_constructor:octopus.GenericTopic)
}

void GenericTopic::SharedCtor() {
  msg_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  _cached_size_ = 0;
}

GenericTopic::~GenericTopic() {
  // @@protoc_insertion_point(destructor:octopus.GenericTopic)
  SharedDtor();
}

void GenericTopic::SharedDtor() {
  msg_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

void GenericTopic::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* GenericTopic::descriptor() {
  protobuf_protobuf_2ftopic_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_protobuf_2ftopic_2eproto::file_level_metadata[kIndexInFileMessages].descriptor;
}

const GenericTopic& GenericTopic::default_instance() {
  protobuf_protobuf_2ftopic_2eproto::InitDefaults();
  return *internal_default_instance();
}

GenericTopic* GenericTopic::New(::google::protobuf::Arena* arena) const {
  GenericTopic* n = new GenericTopic;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void GenericTopic::Clear() {
// @@protoc_insertion_point(message_clear_start:octopus.GenericTopic)
  msg_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

bool GenericTopic::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:octopus.GenericTopic)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // string msg = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(10u)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_msg()));
          DO_(::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
            this->msg().data(), this->msg().length(),
            ::google::protobuf::internal::WireFormatLite::PARSE,
            "octopus.GenericTopic.msg"));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormatLite::SkipField(input, tag));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:octopus.GenericTopic)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:octopus.GenericTopic)
  return false;
#undef DO_
}

void GenericTopic::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:octopus.GenericTopic)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // string msg = 1;
  if (this->msg().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->msg().data(), this->msg().length(),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "octopus.GenericTopic.msg");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      1, this->msg(), output);
  }

  // @@protoc_insertion_point(serialize_end:octopus.GenericTopic)
}

::google::protobuf::uint8* GenericTopic::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:octopus.GenericTopic)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // string msg = 1;
  if (this->msg().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->msg().data(), this->msg().length(),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "octopus.GenericTopic.msg");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->msg(), target);
  }

  // @@protoc_insertion_point(serialize_to_array_end:octopus.GenericTopic)
  return target;
}


size_t GenericTopic::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:octopus.GenericTopic)
  size_t total_size = 0;

  // string msg = 1;
  if (this->msg().size() > 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->msg());
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void GenericTopic::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:octopus.GenericTopic)
  GOOGLE_DCHECK_NE(&from, this);
  const GenericTopic* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const GenericTopic>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:octopus.GenericTopic)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:octopus.GenericTopic)
    MergeFrom(*source);
  }
}

void GenericTopic::MergeFrom(const GenericTopic& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:octopus.GenericTopic)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.msg().size() > 0) {

    msg_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.msg_);
  }
}

void GenericTopic::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:octopus.GenericTopic)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void GenericTopic::CopyFrom(const GenericTopic& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:octopus.GenericTopic)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool GenericTopic::IsInitialized() const {
  return true;
}

void GenericTopic::Swap(GenericTopic* other) {
  if (other == this) return;
  InternalSwap(other);
}
void GenericTopic::InternalSwap(GenericTopic* other) {
  msg_.Swap(&other->msg_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata GenericTopic::GetMetadata() const {
  protobuf_protobuf_2ftopic_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_protobuf_2ftopic_2eproto::file_level_metadata[kIndexInFileMessages];
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// GenericTopic

// string msg = 1;
void GenericTopic::clear_msg() {
  msg_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
const ::std::string& GenericTopic::msg() const {
  // @@protoc_insertion_point(field_get:octopus.GenericTopic.msg)
  return msg_.GetNoArena();
}
void GenericTopic::set_msg(const ::std::string& value) {

  msg_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:octopus.GenericTopic.msg)
}
#if LANG_CXX11
void GenericTopic::set_msg(::std::string&& value) {

  msg_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:octopus.GenericTopic.msg)
}
#endif
void GenericTopic::set_msg(const char* value) {
  GOOGLE_DCHECK(value != NULL);

  msg_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:octopus.GenericTopic.msg)
}
void GenericTopic::set_msg(const char* value, size_t size) {

  msg_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:octopus.GenericTopic.msg)
}
::std::string* GenericTopic::mutable_msg() {

  // @@protoc_insertion_point(field_mutable:octopus.GenericTopic.msg)
  return msg_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
::std::string* GenericTopic::release_msg() {
  // @@protoc_insertion_point(field_release:octopus.GenericTopic.msg)

  return msg_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
void GenericTopic::set_allocated_msg(::std::string* msg) {
  if (msg != NULL) {

  } else {

  }
  msg_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), msg);
  // @@protoc_insertion_point(field_set_allocated:octopus.GenericTopic.msg)
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace octopus

// @@protoc_insertion_point(global_scope)
/**/
