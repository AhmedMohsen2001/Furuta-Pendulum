/*
 * File: encoder_arduino_test.c
 *
 * Code generated for Simulink model 'encoder_arduino_test'.
 *
 * Model version                  : 1.7
 * Simulink Coder version         : 9.3 (R2020a) 18-Nov-2019
 * C/C++ source code generated on : Tue Dec 19 17:48:57 2023
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Atmel->AVR
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "encoder_arduino_test.h"
#include "encoder_arduino_test_private.h"
#include "encoder_arduino_test_dt.h"

/* Block signals (default storage) */
B_encoder_arduino_test_T encoder_arduino_test_B;

/* Block states (default storage) */
DW_encoder_arduino_test_T encoder_arduino_test_DW;

/* Real-time model */
RT_MODEL_encoder_arduino_test_T encoder_arduino_test_M_;
RT_MODEL_encoder_arduino_test_T *const encoder_arduino_test_M =
  &encoder_arduino_test_M_;

/* Forward declaration for local functions */
static void matlabCodegenHandle_matlabCodeg(Encoder_arduino_encoder_ardui_T *obj);
void sMultiWordMul(const uint32_T u1[], int16_T n1, const uint32_T u2[], int16_T
                   n2, uint32_T y[], int16_T n)
{
  int16_T i;
  int16_T j;
  int16_T k;
  int16_T ni;
  uint32_T u1i;
  uint32_T yk;
  uint32_T a1;
  uint32_T a0;
  uint32_T b1;
  uint32_T w10;
  uint32_T w01;
  uint32_T cb;
  boolean_T isNegative1;
  boolean_T isNegative2;
  uint32_T cb1;
  uint32_T cb2;
  isNegative1 = ((u1[n1 - 1] & 2147483648UL) != 0UL);
  isNegative2 = ((u2[n2 - 1] & 2147483648UL) != 0UL);
  cb1 = 1UL;

  /* Initialize output to zero */
  for (k = 0; k < n; k++) {
    y[k] = 0UL;
  }

  for (i = 0; i < n1; i++) {
    cb = 0UL;
    u1i = u1[i];
    if (isNegative1) {
      u1i = ~u1i + cb1;
      cb1 = (uint32_T)(u1i < cb1);
    }

    a1 = u1i >> 16U;
    a0 = u1i & 65535UL;
    cb2 = 1UL;
    ni = n - i;
    ni = n2 <= ni ? n2 : ni;
    k = i;
    for (j = 0; j < ni; j++) {
      u1i = u2[j];
      if (isNegative2) {
        u1i = ~u1i + cb2;
        cb2 = (uint32_T)(u1i < cb2);
      }

      b1 = u1i >> 16U;
      u1i &= 65535UL;
      w10 = a1 * u1i;
      w01 = a0 * b1;
      yk = y[k] + cb;
      cb = (uint32_T)(yk < cb);
      u1i *= a0;
      yk += u1i;
      cb += (yk < u1i);
      u1i = w10 << 16U;
      yk += u1i;
      cb += (yk < u1i);
      u1i = w01 << 16U;
      yk += u1i;
      cb += (yk < u1i);
      y[k] = yk;
      cb += w10 >> 16U;
      cb += w01 >> 16U;
      cb += a1 * b1;
      k++;
    }

    if (k < n) {
      y[k] = cb;
    }
  }

  /* Apply sign */
  if (isNegative1 != isNegative2) {
    cb = 1UL;
    for (k = 0; k < n; k++) {
      yk = ~y[k] + cb;
      y[k] = yk;
      cb = (uint32_T)(yk < cb);
    }
  }
}

static void matlabCodegenHandle_matlabCodeg(Encoder_arduino_encoder_ardui_T *obj)
{
  if (!obj->matlabCodegenIsDeleted) {
    obj->matlabCodegenIsDeleted = true;
  }
}

/* Model step function */
void encoder_arduino_test_step(void)
{
  int32_T rtb_MATLABSystem_0;
  uint32_T tmp;
  uint32_T tmp_0;

  /* MATLABSystem: '<Root>/MATLAB System' */
  if (encoder_arduino_test_DW.obj.SampleTime !=
      encoder_arduino_test_P.MATLABSystem_SampleTime) {
    encoder_arduino_test_DW.obj.SampleTime =
      encoder_arduino_test_P.MATLABSystem_SampleTime;
  }

  rtb_MATLABSystem_0 = enc_output(0.0);

  /* Gain: '<Root>/Gain' incorporates:
   *  MATLABSystem: '<Root>/MATLAB System'
   */
  tmp = (uint32_T)encoder_arduino_test_P.Gain_Gain;
  tmp_0 = (uint32_T)rtb_MATLABSystem_0;
  sMultiWordMul(&tmp, 1, &tmp_0, 1, &encoder_arduino_test_B.Gain.chunks[0U], 2);

  /* External mode */
  rtExtModeUploadCheckTrigger(1);

  {                                    /* Sample time: [0.01s, 0.0s] */
    rtExtModeUpload(0, (real_T)encoder_arduino_test_M->Timing.taskTime0);
  }

  /* signal main to stop simulation */
  {                                    /* Sample time: [0.01s, 0.0s] */
    if ((rtmGetTFinal(encoder_arduino_test_M)!=-1) &&
        !((rtmGetTFinal(encoder_arduino_test_M)-
           encoder_arduino_test_M->Timing.taskTime0) >
          encoder_arduino_test_M->Timing.taskTime0 * (DBL_EPSILON))) {
      rtmSetErrorStatus(encoder_arduino_test_M, "Simulation finished");
    }

    if (rtmGetStopRequested(encoder_arduino_test_M)) {
      rtmSetErrorStatus(encoder_arduino_test_M, "Simulation finished");
    }
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   */
  encoder_arduino_test_M->Timing.taskTime0 =
    ((time_T)(++encoder_arduino_test_M->Timing.clockTick0)) *
    encoder_arduino_test_M->Timing.stepSize0;
}

/* Model initialize function */
void encoder_arduino_test_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));
  rtmSetTFinal(encoder_arduino_test_M, -1);
  encoder_arduino_test_M->Timing.stepSize0 = 0.01;

  /* External mode info */
  encoder_arduino_test_M->Sizes.checksums[0] = (1471637138U);
  encoder_arduino_test_M->Sizes.checksums[1] = (2777156986U);
  encoder_arduino_test_M->Sizes.checksums[2] = (4102537185U);
  encoder_arduino_test_M->Sizes.checksums[3] = (1922003867U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[2];
    encoder_arduino_test_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(encoder_arduino_test_M->extModeInfo,
      &encoder_arduino_test_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(encoder_arduino_test_M->extModeInfo,
                        encoder_arduino_test_M->Sizes.checksums);
    rteiSetTPtr(encoder_arduino_test_M->extModeInfo, rtmGetTPtr
                (encoder_arduino_test_M));
  }

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    encoder_arduino_test_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 31;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Start for MATLABSystem: '<Root>/MATLAB System' */
  encoder_arduino_test_DW.obj.matlabCodegenIsDeleted = false;
  encoder_arduino_test_DW.obj.SampleTime =
    encoder_arduino_test_P.MATLABSystem_SampleTime;
  encoder_arduino_test_DW.obj.isInitialized = 1L;
  enc_init(0.0, 2.0, 3.0);
  encoder_arduino_test_DW.obj.isSetupComplete = true;
}

/* Model terminate function */
void encoder_arduino_test_terminate(void)
{
  /* Terminate for MATLABSystem: '<Root>/MATLAB System' */
  matlabCodegenHandle_matlabCodeg(&encoder_arduino_test_DW.obj);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
