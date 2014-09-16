# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: WPB.proto

from google.protobuf.internal import enum_type_wrapper
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)




DESCRIPTOR = _descriptor.FileDescriptor(
  name='WPB.proto',
  package='',
  serialized_pb='\n\tWPB.proto\"Q\n\x06ReqGet\x12\x0f\n\x07imageID\x18\x01 \x02(\t\x12\r\n\x05width\x18\x02 \x02(\x05\x12\x0e\n\x06height\x18\x03 \x02(\x05\x12\x17\n\x0fkeep_proportion\x18\x04 \x02(\x08\"(\n\x06ReqSet\x12\x11\n\timageName\x18\x01 \x01(\t\x12\x0b\n\x03md5\x18\x02 \x02(\t\".\n\x08NodeInfo\x12\x10\n\x08nodeAddr\x18\x01 \x02(\t\x12\x10\n\x08nodePort\x18\x02 \x02(\x05\"T\n\x0bReqResponse\x12\x19\n\x07rspCode\x18\x01 \x02(\x0e\x32\x08.RspCode\x12\x19\n\x07\x65rrCode\x18\x02 \x01(\x0e\x32\x08.ErrCode\x12\x0f\n\x07newname\x18\x03 \x01(\t**\n\x07RspCode\x12\x0e\n\nREQ_FAILED\x10\x00\x12\x0f\n\x0bREQ_SUCCESS\x10\x01*9\n\x07\x45rrCode\x12\x16\n\x12\x45RR_FILE_NOT_FOUND\x10\x00\x12\x16\n\x12\x45RR_INVALID_PARAMS\x10\x01')

_RSPCODE = _descriptor.EnumDescriptor(
  name='RspCode',
  full_name='RspCode',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='REQ_FAILED', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='REQ_SUCCESS', index=1, number=1,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=272,
  serialized_end=314,
)

RspCode = enum_type_wrapper.EnumTypeWrapper(_RSPCODE)
_ERRCODE = _descriptor.EnumDescriptor(
  name='ErrCode',
  full_name='ErrCode',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='ERR_FILE_NOT_FOUND', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_INVALID_PARAMS', index=1, number=1,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=316,
  serialized_end=373,
)

ErrCode = enum_type_wrapper.EnumTypeWrapper(_ERRCODE)
REQ_FAILED = 0
REQ_SUCCESS = 1
ERR_FILE_NOT_FOUND = 0
ERR_INVALID_PARAMS = 1



_REQGET = _descriptor.Descriptor(
  name='ReqGet',
  full_name='ReqGet',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='imageID', full_name='ReqGet.imageID', index=0,
      number=1, type=9, cpp_type=9, label=2,
      has_default_value=False, default_value=unicode("", "utf-8"),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='width', full_name='ReqGet.width', index=1,
      number=2, type=5, cpp_type=1, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='height', full_name='ReqGet.height', index=2,
      number=3, type=5, cpp_type=1, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='keep_proportion', full_name='ReqGet.keep_proportion', index=3,
      number=4, type=8, cpp_type=7, label=2,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  serialized_start=13,
  serialized_end=94,
)


_REQSET = _descriptor.Descriptor(
  name='ReqSet',
  full_name='ReqSet',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='imageName', full_name='ReqSet.imageName', index=0,
      number=1, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=unicode("", "utf-8"),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='md5', full_name='ReqSet.md5', index=1,
      number=2, type=9, cpp_type=9, label=2,
      has_default_value=False, default_value=unicode("", "utf-8"),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  serialized_start=96,
  serialized_end=136,
)


_NODEINFO = _descriptor.Descriptor(
  name='NodeInfo',
  full_name='NodeInfo',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='nodeAddr', full_name='NodeInfo.nodeAddr', index=0,
      number=1, type=9, cpp_type=9, label=2,
      has_default_value=False, default_value=unicode("", "utf-8"),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='nodePort', full_name='NodeInfo.nodePort', index=1,
      number=2, type=5, cpp_type=1, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  serialized_start=138,
  serialized_end=184,
)


_REQRESPONSE = _descriptor.Descriptor(
  name='ReqResponse',
  full_name='ReqResponse',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='rspCode', full_name='ReqResponse.rspCode', index=0,
      number=1, type=14, cpp_type=8, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='errCode', full_name='ReqResponse.errCode', index=1,
      number=2, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='newname', full_name='ReqResponse.newname', index=2,
      number=3, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=unicode("", "utf-8"),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  serialized_start=186,
  serialized_end=270,
)

_REQRESPONSE.fields_by_name['rspCode'].enum_type = _RSPCODE
_REQRESPONSE.fields_by_name['errCode'].enum_type = _ERRCODE
DESCRIPTOR.message_types_by_name['ReqGet'] = _REQGET
DESCRIPTOR.message_types_by_name['ReqSet'] = _REQSET
DESCRIPTOR.message_types_by_name['NodeInfo'] = _NODEINFO
DESCRIPTOR.message_types_by_name['ReqResponse'] = _REQRESPONSE

class ReqGet(_message.Message):
  __metaclass__ = _reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _REQGET

  # @@protoc_insertion_point(class_scope:ReqGet)

class ReqSet(_message.Message):
  __metaclass__ = _reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _REQSET

  # @@protoc_insertion_point(class_scope:ReqSet)

class NodeInfo(_message.Message):
  __metaclass__ = _reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _NODEINFO

  # @@protoc_insertion_point(class_scope:NodeInfo)

class ReqResponse(_message.Message):
  __metaclass__ = _reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _REQRESPONSE

  # @@protoc_insertion_point(class_scope:ReqResponse)


# @@protoc_insertion_point(module_scope)