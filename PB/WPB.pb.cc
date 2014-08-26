// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: WPB.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "WPB.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace {

const ::google::protobuf::Descriptor* ReqGet_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  ReqGet_reflection_ = NULL;
const ::google::protobuf::Descriptor* ReqSet_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  ReqSet_reflection_ = NULL;
const ::google::protobuf::Descriptor* ReqResponse_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  ReqResponse_reflection_ = NULL;
const ::google::protobuf::EnumDescriptor* RspCode_descriptor_ = NULL;
const ::google::protobuf::EnumDescriptor* ErrCode_descriptor_ = NULL;

}  // namespace


void protobuf_AssignDesc_WPB_2eproto() {
  protobuf_AddDesc_WPB_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "WPB.proto");
  GOOGLE_CHECK(file != NULL);
  ReqGet_descriptor_ = file->message_type(0);
  static const int ReqGet_offsets_[3] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ReqGet, imageid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ReqGet, width_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ReqGet, height_),
  };
  ReqGet_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      ReqGet_descriptor_,
      ReqGet::default_instance_,
      ReqGet_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ReqGet, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ReqGet, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(ReqGet));
  ReqSet_descriptor_ = file->message_type(1);
  static const int ReqSet_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ReqSet, imagename_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ReqSet, imagebuff_),
  };
  ReqSet_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      ReqSet_descriptor_,
      ReqSet::default_instance_,
      ReqSet_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ReqSet, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ReqSet, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(ReqSet));
  ReqResponse_descriptor_ = file->message_type(2);
  static const int ReqResponse_offsets_[3] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ReqResponse, rspcode_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ReqResponse, errcode_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ReqResponse, newname_),
  };
  ReqResponse_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      ReqResponse_descriptor_,
      ReqResponse::default_instance_,
      ReqResponse_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ReqResponse, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ReqResponse, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(ReqResponse));
  RspCode_descriptor_ = file->enum_type(0);
  ErrCode_descriptor_ = file->enum_type(1);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_WPB_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    ReqGet_descriptor_, &ReqGet::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    ReqSet_descriptor_, &ReqSet::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    ReqResponse_descriptor_, &ReqResponse::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_WPB_2eproto() {
  delete ReqGet::default_instance_;
  delete ReqGet_reflection_;
  delete ReqSet::default_instance_;
  delete ReqSet_reflection_;
  delete ReqResponse::default_instance_;
  delete ReqResponse_reflection_;
}

void protobuf_AddDesc_WPB_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\tWPB.proto\"8\n\006ReqGet\022\017\n\007imageID\030\001 \002(\t\022\r"
    "\n\005width\030\002 \002(\005\022\016\n\006height\030\003 \002(\005\".\n\006ReqSet\022"
    "\021\n\timageName\030\001 \002(\t\022\021\n\timageBuff\030\002 \002(\t\"T\n"
    "\013ReqResponse\022\031\n\007rspCode\030\001 \002(\0162\010.RspCode\022"
    "\031\n\007errCode\030\002 \001(\0162\010.ErrCode\022\017\n\007newname\030\003 "
    "\001(\t**\n\007RspCode\022\016\n\nREQ_FAILED\020\000\022\017\n\013REQ_SU"
    "CCESS\020\001*9\n\007ErrCode\022\026\n\022ERR_FILE_NOT_FOUND"
    "\020\000\022\026\n\022ERR_INVALID_PARAMS\020\001", 306);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "WPB.proto", &protobuf_RegisterTypes);
  ReqGet::default_instance_ = new ReqGet();
  ReqSet::default_instance_ = new ReqSet();
  ReqResponse::default_instance_ = new ReqResponse();
  ReqGet::default_instance_->InitAsDefaultInstance();
  ReqSet::default_instance_->InitAsDefaultInstance();
  ReqResponse::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_WPB_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_WPB_2eproto {
  StaticDescriptorInitializer_WPB_2eproto() {
    protobuf_AddDesc_WPB_2eproto();
  }
} static_descriptor_initializer_WPB_2eproto_;
const ::google::protobuf::EnumDescriptor* RspCode_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return RspCode_descriptor_;
}
bool RspCode_IsValid(int value) {
  switch(value) {
    case 0:
    case 1:
      return true;
    default:
      return false;
  }
}

const ::google::protobuf::EnumDescriptor* ErrCode_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return ErrCode_descriptor_;
}
bool ErrCode_IsValid(int value) {
  switch(value) {
    case 0:
    case 1:
      return true;
    default:
      return false;
  }
}


// ===================================================================

#ifndef _MSC_VER
const int ReqGet::kImageIDFieldNumber;
const int ReqGet::kWidthFieldNumber;
const int ReqGet::kHeightFieldNumber;
#endif  // !_MSC_VER

ReqGet::ReqGet()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void ReqGet::InitAsDefaultInstance() {
}

ReqGet::ReqGet(const ReqGet& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void ReqGet::SharedCtor() {
  _cached_size_ = 0;
  imageid_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  width_ = 0;
  height_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

ReqGet::~ReqGet() {
  SharedDtor();
}

void ReqGet::SharedDtor() {
  if (imageid_ != &::google::protobuf::internal::kEmptyString) {
    delete imageid_;
  }
  if (this != default_instance_) {
  }
}

void ReqGet::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* ReqGet::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return ReqGet_descriptor_;
}

const ReqGet& ReqGet::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_WPB_2eproto();
  return *default_instance_;
}

ReqGet* ReqGet::default_instance_ = NULL;

ReqGet* ReqGet::New() const {
  return new ReqGet;
}

void ReqGet::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (has_imageid()) {
      if (imageid_ != &::google::protobuf::internal::kEmptyString) {
        imageid_->clear();
      }
    }
    width_ = 0;
    height_ = 0;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool ReqGet::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required string imageID = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_imageid()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->imageid().data(), this->imageid().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_width;
        break;
      }

      // required int32 width = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_width:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &width_)));
          set_has_width();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(24)) goto parse_height;
        break;
      }

      // required int32 height = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_height:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &height_)));
          set_has_height();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }

      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void ReqGet::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required string imageID = 1;
  if (has_imageid()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->imageid().data(), this->imageid().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      1, this->imageid(), output);
  }

  // required int32 width = 2;
  if (has_width()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(2, this->width(), output);
  }

  // required int32 height = 3;
  if (has_height()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(3, this->height(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* ReqGet::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required string imageID = 1;
  if (has_imageid()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->imageid().data(), this->imageid().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->imageid(), target);
  }

  // required int32 width = 2;
  if (has_width()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(2, this->width(), target);
  }

  // required int32 height = 3;
  if (has_height()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(3, this->height(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int ReqGet::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required string imageID = 1;
    if (has_imageid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->imageid());
    }

    // required int32 width = 2;
    if (has_width()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->width());
    }

    // required int32 height = 3;
    if (has_height()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->height());
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void ReqGet::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const ReqGet* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const ReqGet*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void ReqGet::MergeFrom(const ReqGet& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_imageid()) {
      set_imageid(from.imageid());
    }
    if (from.has_width()) {
      set_width(from.width());
    }
    if (from.has_height()) {
      set_height(from.height());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void ReqGet::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void ReqGet::CopyFrom(const ReqGet& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ReqGet::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000007) != 0x00000007) return false;

  return true;
}

void ReqGet::Swap(ReqGet* other) {
  if (other != this) {
    std::swap(imageid_, other->imageid_);
    std::swap(width_, other->width_);
    std::swap(height_, other->height_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata ReqGet::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = ReqGet_descriptor_;
  metadata.reflection = ReqGet_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int ReqSet::kImageNameFieldNumber;
const int ReqSet::kImageBuffFieldNumber;
#endif  // !_MSC_VER

ReqSet::ReqSet()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void ReqSet::InitAsDefaultInstance() {
}

ReqSet::ReqSet(const ReqSet& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void ReqSet::SharedCtor() {
  _cached_size_ = 0;
  imagename_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  imagebuff_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

ReqSet::~ReqSet() {
  SharedDtor();
}

void ReqSet::SharedDtor() {
  if (imagename_ != &::google::protobuf::internal::kEmptyString) {
    delete imagename_;
  }
  if (imagebuff_ != &::google::protobuf::internal::kEmptyString) {
    delete imagebuff_;
  }
  if (this != default_instance_) {
  }
}

void ReqSet::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* ReqSet::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return ReqSet_descriptor_;
}

const ReqSet& ReqSet::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_WPB_2eproto();
  return *default_instance_;
}

ReqSet* ReqSet::default_instance_ = NULL;

ReqSet* ReqSet::New() const {
  return new ReqSet;
}

void ReqSet::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (has_imagename()) {
      if (imagename_ != &::google::protobuf::internal::kEmptyString) {
        imagename_->clear();
      }
    }
    if (has_imagebuff()) {
      if (imagebuff_ != &::google::protobuf::internal::kEmptyString) {
        imagebuff_->clear();
      }
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool ReqSet::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required string imageName = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_imagename()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->imagename().data(), this->imagename().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(18)) goto parse_imageBuff;
        break;
      }

      // required string imageBuff = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_imageBuff:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_imagebuff()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->imagebuff().data(), this->imagebuff().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }

      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void ReqSet::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required string imageName = 1;
  if (has_imagename()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->imagename().data(), this->imagename().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      1, this->imagename(), output);
  }

  // required string imageBuff = 2;
  if (has_imagebuff()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->imagebuff().data(), this->imagebuff().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      2, this->imagebuff(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* ReqSet::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required string imageName = 1;
  if (has_imagename()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->imagename().data(), this->imagename().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->imagename(), target);
  }

  // required string imageBuff = 2;
  if (has_imagebuff()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->imagebuff().data(), this->imagebuff().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->imagebuff(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int ReqSet::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required string imageName = 1;
    if (has_imagename()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->imagename());
    }

    // required string imageBuff = 2;
    if (has_imagebuff()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->imagebuff());
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void ReqSet::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const ReqSet* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const ReqSet*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void ReqSet::MergeFrom(const ReqSet& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_imagename()) {
      set_imagename(from.imagename());
    }
    if (from.has_imagebuff()) {
      set_imagebuff(from.imagebuff());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void ReqSet::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void ReqSet::CopyFrom(const ReqSet& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ReqSet::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;

  return true;
}

void ReqSet::Swap(ReqSet* other) {
  if (other != this) {
    std::swap(imagename_, other->imagename_);
    std::swap(imagebuff_, other->imagebuff_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata ReqSet::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = ReqSet_descriptor_;
  metadata.reflection = ReqSet_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int ReqResponse::kRspCodeFieldNumber;
const int ReqResponse::kErrCodeFieldNumber;
const int ReqResponse::kNewnameFieldNumber;
#endif  // !_MSC_VER

ReqResponse::ReqResponse()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void ReqResponse::InitAsDefaultInstance() {
}

ReqResponse::ReqResponse(const ReqResponse& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void ReqResponse::SharedCtor() {
  _cached_size_ = 0;
  rspcode_ = 0;
  errcode_ = 0;
  newname_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

ReqResponse::~ReqResponse() {
  SharedDtor();
}

void ReqResponse::SharedDtor() {
  if (newname_ != &::google::protobuf::internal::kEmptyString) {
    delete newname_;
  }
  if (this != default_instance_) {
  }
}

void ReqResponse::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* ReqResponse::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return ReqResponse_descriptor_;
}

const ReqResponse& ReqResponse::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_WPB_2eproto();
  return *default_instance_;
}

ReqResponse* ReqResponse::default_instance_ = NULL;

ReqResponse* ReqResponse::New() const {
  return new ReqResponse;
}

void ReqResponse::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    rspcode_ = 0;
    errcode_ = 0;
    if (has_newname()) {
      if (newname_ != &::google::protobuf::internal::kEmptyString) {
        newname_->clear();
      }
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool ReqResponse::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required .RspCode rspCode = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::RspCode_IsValid(value)) {
            set_rspcode(static_cast< ::RspCode >(value));
          } else {
            mutable_unknown_fields()->AddVarint(1, value);
          }
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_errCode;
        break;
      }

      // optional .ErrCode errCode = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_errCode:
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::ErrCode_IsValid(value)) {
            set_errcode(static_cast< ::ErrCode >(value));
          } else {
            mutable_unknown_fields()->AddVarint(2, value);
          }
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(26)) goto parse_newname;
        break;
      }

      // optional string newname = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_newname:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_newname()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->newname().data(), this->newname().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }

      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void ReqResponse::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required .RspCode rspCode = 1;
  if (has_rspcode()) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      1, this->rspcode(), output);
  }

  // optional .ErrCode errCode = 2;
  if (has_errcode()) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      2, this->errcode(), output);
  }

  // optional string newname = 3;
  if (has_newname()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->newname().data(), this->newname().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      3, this->newname(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* ReqResponse::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required .RspCode rspCode = 1;
  if (has_rspcode()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      1, this->rspcode(), target);
  }

  // optional .ErrCode errCode = 2;
  if (has_errcode()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      2, this->errcode(), target);
  }

  // optional string newname = 3;
  if (has_newname()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->newname().data(), this->newname().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        3, this->newname(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int ReqResponse::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required .RspCode rspCode = 1;
    if (has_rspcode()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->rspcode());
    }

    // optional .ErrCode errCode = 2;
    if (has_errcode()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->errcode());
    }

    // optional string newname = 3;
    if (has_newname()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->newname());
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void ReqResponse::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const ReqResponse* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const ReqResponse*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void ReqResponse::MergeFrom(const ReqResponse& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_rspcode()) {
      set_rspcode(from.rspcode());
    }
    if (from.has_errcode()) {
      set_errcode(from.errcode());
    }
    if (from.has_newname()) {
      set_newname(from.newname());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void ReqResponse::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void ReqResponse::CopyFrom(const ReqResponse& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ReqResponse::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;

  return true;
}

void ReqResponse::Swap(ReqResponse* other) {
  if (other != this) {
    std::swap(rspcode_, other->rspcode_);
    std::swap(errcode_, other->errcode_);
    std::swap(newname_, other->newname_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata ReqResponse::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = ReqResponse_descriptor_;
  metadata.reflection = ReqResponse_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)
