/* /opt/PV6.0.pl1/prog/curdir/sylvain/ParaVision/methods/src/sl_radialT1_2D/initMeth.c */
void initMeth(void);
/* /opt/PV6.0.pl1/prog/curdir/sylvain/ParaVision/methods/src/sl_radialT1_2D/loadMeth.c */
void loadMeth(const char *);
/* /opt/PV6.0.pl1/prog/curdir/sylvain/ParaVision/methods/src/sl_radialT1_2D/parsRelations.c */
void ExcPulse1EnumRel(void);
void ExcPulse1AmplRel(void);
void HandleRFPulseAmplitude(void);
void ExcPulse1Rel(void);
void ExcPulse1Range(void);
void RepetitionTimeRange(void);
void RepetitionTimeRel(void);
void AveragesRange(void);
void AveragesRel(void);
void ProUnderRel(void);
void ProUnderRange(void);
void RampModeRel(void);
void RampModeInitRel(void);
void SlewRateRel(void);
void SlewRateRange(void);
void ConstantTimeRange(void);
void UpdateAdjustments(void);
void SliceSpoilerRel(void);
void EchoPositionRange(void);
void EffSWhRange(void);
void EffSWhRel(void);
void BinomialFunc(void);
void ExcPulseBinEnumRelation(void);
void ExcPulseBinRange(void);
void ExcPulseBinRelation(void);
void ExcPulseBinAmplRelation(void);
void HandleRFPulseBinAmplitudes(void);
void VariableFlipAngle(void);
/* /opt/PV6.0.pl1/prog/curdir/sylvain/ParaVision/methods/src/sl_radialT1_2D/backbone.c */
void backbone(void);
void UpdateIr(void);
void UpdateEchoTime(double *const , double *const );
void UpdateRepetitionTime(void);
void UpdateMP2RAGE_TR(void);
void UpdateRFSpoiling(void);
void LocalFrequencyOffsetRels(void);
void UpdateGeometry(double *, double);
double EncodingLimits(int, double *, double);
void EncodingGradients(double, double, double);
void EncodingDephGradients(void);
YesNo UpdateSliceSelectionGradients(const double, const double, double);
void UpdateRFPulses(void);
void ControlGradientLimits(void);
int lcm(int, int);
int gcd(int, int);
void UpdateRFPulsesBin(void);
/* /opt/PV6.0.pl1/prog/curdir/sylvain/ParaVision/methods/src/sl_radialT1_2D/BaseLevelRelations.c */
void SetBaseLevelParam(void);
void SetBasicParameters(void);
void SetFrequencyParameters(void);
void SetGradientParameters(void);
void SetPpgParameters(void);
void SetInfoParameters(void);
void SetMachineParameters(void);
void PrintTimingInfo(void);
int SetProj(double *, double *, const int, const double);
/* /opt/PV6.0.pl1/prog/curdir/sylvain/ParaVision/methods/src/sl_radialT1_2D/RecoRelations.c */
void SetRecoParam(void);
void RecoDerive(void);
/* /opt/PV6.0.pl1/prog/curdir/sylvain/ParaVision/methods/src/sl_radialT1_2D/deriveVisu.c */
void deriveVisu(void);
