/* AUTOGENERATED FILE. DO NOT EDIT. */
#include <string.h>
#include <stdlib.h>
#include <setjmp.h>
#include "cmock.h"
#include "mock_led.h"

static const char* CMockString_index = "index";
static const char* CMockString_led_turn_off = "led_turn_off";
static const char* CMockString_led_turn_on = "led_turn_on";

typedef struct _CMOCK_led_turn_off_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;
  int CallOrder;
  uint8_t Expected_index;

} CMOCK_led_turn_off_CALL_INSTANCE;

typedef struct _CMOCK_led_turn_on_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;
  int CallOrder;
  uint8_t Expected_index;

} CMOCK_led_turn_on_CALL_INSTANCE;

static struct mock_ledInstance
{
  char led_turn_off_IgnoreBool;
  char led_turn_off_CallbackBool;
  CMOCK_led_turn_off_CALLBACK led_turn_off_CallbackFunctionPointer;
  int led_turn_off_CallbackCalls;
  CMOCK_MEM_INDEX_TYPE led_turn_off_CallInstance;
  char led_turn_on_IgnoreBool;
  char led_turn_on_CallbackBool;
  CMOCK_led_turn_on_CALLBACK led_turn_on_CallbackFunctionPointer;
  int led_turn_on_CallbackCalls;
  CMOCK_MEM_INDEX_TYPE led_turn_on_CallInstance;
} Mock;

extern jmp_buf AbortFrame;
extern int GlobalExpectCount;
extern int GlobalVerifyOrder;

void mock_led_Verify(void)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  CMOCK_MEM_INDEX_TYPE call_instance;
  call_instance = Mock.led_turn_off_CallInstance;
  if (Mock.led_turn_off_IgnoreBool)
    call_instance = CMOCK_GUTS_NONE;
  if (CMOCK_GUTS_NONE != call_instance)
  {
    UNITY_SET_DETAIL(CMockString_led_turn_off);
    UNITY_TEST_FAIL(cmock_line, CMockStringCalledLess);
  }
  if (Mock.led_turn_off_CallbackFunctionPointer != NULL)
  {
    call_instance = CMOCK_GUTS_NONE;
    (void)call_instance;
  }
  call_instance = Mock.led_turn_on_CallInstance;
  if (Mock.led_turn_on_IgnoreBool)
    call_instance = CMOCK_GUTS_NONE;
  if (CMOCK_GUTS_NONE != call_instance)
  {
    UNITY_SET_DETAIL(CMockString_led_turn_on);
    UNITY_TEST_FAIL(cmock_line, CMockStringCalledLess);
  }
  if (Mock.led_turn_on_CallbackFunctionPointer != NULL)
  {
    call_instance = CMOCK_GUTS_NONE;
    (void)call_instance;
  }
}

void mock_led_Init(void)
{
  mock_led_Destroy();
}

void mock_led_Destroy(void)
{
  CMock_Guts_MemFreeAll();
  memset(&Mock, 0, sizeof(Mock));
  GlobalExpectCount = 0;
  GlobalVerifyOrder = 0;
}

void led_turn_off(uint8_t index)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  CMOCK_led_turn_off_CALL_INSTANCE* cmock_call_instance;
  UNITY_SET_DETAIL(CMockString_led_turn_off);
  cmock_call_instance = (CMOCK_led_turn_off_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.led_turn_off_CallInstance);
  Mock.led_turn_off_CallInstance = CMock_Guts_MemNext(Mock.led_turn_off_CallInstance);
  if (Mock.led_turn_off_IgnoreBool)
  {
    UNITY_CLR_DETAILS();
    return;
  }
  if (!Mock.led_turn_off_CallbackBool &&
      Mock.led_turn_off_CallbackFunctionPointer != NULL)
  {
    Mock.led_turn_off_CallbackFunctionPointer(index, Mock.led_turn_off_CallbackCalls++);
    UNITY_CLR_DETAILS();
    return;
  }
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringCalledMore);
  cmock_line = cmock_call_instance->LineNumber;
  if (cmock_call_instance->CallOrder > ++GlobalVerifyOrder)
    UNITY_TEST_FAIL(cmock_line, CMockStringCalledEarly);
  if (cmock_call_instance->CallOrder < GlobalVerifyOrder)
    UNITY_TEST_FAIL(cmock_line, CMockStringCalledLate);
  {
    UNITY_SET_DETAILS(CMockString_led_turn_off,CMockString_index);
    UNITY_TEST_ASSERT_EQUAL_HEX8(cmock_call_instance->Expected_index, index, cmock_line, CMockStringMismatch);
  }
  if (Mock.led_turn_off_CallbackFunctionPointer != NULL)
  {
    Mock.led_turn_off_CallbackFunctionPointer(index, Mock.led_turn_off_CallbackCalls++);
  }
  UNITY_CLR_DETAILS();
}

void CMockExpectParameters_led_turn_off(CMOCK_led_turn_off_CALL_INSTANCE* cmock_call_instance, uint8_t index);
void CMockExpectParameters_led_turn_off(CMOCK_led_turn_off_CALL_INSTANCE* cmock_call_instance, uint8_t index)
{
  cmock_call_instance->Expected_index = index;
}

void led_turn_off_CMockIgnore(void)
{
  Mock.led_turn_off_IgnoreBool = (char)1;
}

void led_turn_off_CMockStopIgnore(void)
{
  Mock.led_turn_off_IgnoreBool = (char)0;
}

void led_turn_off_CMockExpect(UNITY_LINE_TYPE cmock_line, uint8_t index)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_led_turn_off_CALL_INSTANCE));
  CMOCK_led_turn_off_CALL_INSTANCE* cmock_call_instance = (CMOCK_led_turn_off_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.led_turn_off_CallInstance = CMock_Guts_MemChain(Mock.led_turn_off_CallInstance, cmock_guts_index);
  Mock.led_turn_off_IgnoreBool = (char)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->CallOrder = ++GlobalExpectCount;
  CMockExpectParameters_led_turn_off(cmock_call_instance, index);
}

void led_turn_off_AddCallback(CMOCK_led_turn_off_CALLBACK Callback)
{
  Mock.led_turn_off_IgnoreBool = (char)0;
  Mock.led_turn_off_CallbackBool = (char)1;
  Mock.led_turn_off_CallbackFunctionPointer = Callback;
}

void led_turn_off_Stub(CMOCK_led_turn_off_CALLBACK Callback)
{
  Mock.led_turn_off_IgnoreBool = (char)0;
  Mock.led_turn_off_CallbackBool = (char)0;
  Mock.led_turn_off_CallbackFunctionPointer = Callback;
}

void led_turn_on(uint8_t index)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  CMOCK_led_turn_on_CALL_INSTANCE* cmock_call_instance;
  UNITY_SET_DETAIL(CMockString_led_turn_on);
  cmock_call_instance = (CMOCK_led_turn_on_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.led_turn_on_CallInstance);
  Mock.led_turn_on_CallInstance = CMock_Guts_MemNext(Mock.led_turn_on_CallInstance);
  if (Mock.led_turn_on_IgnoreBool)
  {
    UNITY_CLR_DETAILS();
    return;
  }
  if (!Mock.led_turn_on_CallbackBool &&
      Mock.led_turn_on_CallbackFunctionPointer != NULL)
  {
    Mock.led_turn_on_CallbackFunctionPointer(index, Mock.led_turn_on_CallbackCalls++);
    UNITY_CLR_DETAILS();
    return;
  }
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringCalledMore);
  cmock_line = cmock_call_instance->LineNumber;
  if (cmock_call_instance->CallOrder > ++GlobalVerifyOrder)
    UNITY_TEST_FAIL(cmock_line, CMockStringCalledEarly);
  if (cmock_call_instance->CallOrder < GlobalVerifyOrder)
    UNITY_TEST_FAIL(cmock_line, CMockStringCalledLate);
  {
    UNITY_SET_DETAILS(CMockString_led_turn_on,CMockString_index);
    UNITY_TEST_ASSERT_EQUAL_HEX8(cmock_call_instance->Expected_index, index, cmock_line, CMockStringMismatch);
  }
  if (Mock.led_turn_on_CallbackFunctionPointer != NULL)
  {
    Mock.led_turn_on_CallbackFunctionPointer(index, Mock.led_turn_on_CallbackCalls++);
  }
  UNITY_CLR_DETAILS();
}

void CMockExpectParameters_led_turn_on(CMOCK_led_turn_on_CALL_INSTANCE* cmock_call_instance, uint8_t index);
void CMockExpectParameters_led_turn_on(CMOCK_led_turn_on_CALL_INSTANCE* cmock_call_instance, uint8_t index)
{
  cmock_call_instance->Expected_index = index;
}

void led_turn_on_CMockIgnore(void)
{
  Mock.led_turn_on_IgnoreBool = (char)1;
}

void led_turn_on_CMockStopIgnore(void)
{
  Mock.led_turn_on_IgnoreBool = (char)0;
}

void led_turn_on_CMockExpect(UNITY_LINE_TYPE cmock_line, uint8_t index)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_led_turn_on_CALL_INSTANCE));
  CMOCK_led_turn_on_CALL_INSTANCE* cmock_call_instance = (CMOCK_led_turn_on_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.led_turn_on_CallInstance = CMock_Guts_MemChain(Mock.led_turn_on_CallInstance, cmock_guts_index);
  Mock.led_turn_on_IgnoreBool = (char)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->CallOrder = ++GlobalExpectCount;
  CMockExpectParameters_led_turn_on(cmock_call_instance, index);
}

void led_turn_on_AddCallback(CMOCK_led_turn_on_CALLBACK Callback)
{
  Mock.led_turn_on_IgnoreBool = (char)0;
  Mock.led_turn_on_CallbackBool = (char)1;
  Mock.led_turn_on_CallbackFunctionPointer = Callback;
}

void led_turn_on_Stub(CMOCK_led_turn_on_CALLBACK Callback)
{
  Mock.led_turn_on_IgnoreBool = (char)0;
  Mock.led_turn_on_CallbackBool = (char)0;
  Mock.led_turn_on_CallbackFunctionPointer = Callback;
}

