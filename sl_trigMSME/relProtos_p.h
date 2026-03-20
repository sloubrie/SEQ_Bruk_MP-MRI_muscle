/* /opt/PV6.0.1/prog/curdir/sylvain/ParaVision/methods/src/sl_trigMSME/initMeth.c */
void initMeth(void);
/* /opt/PV6.0.1/prog/curdir/sylvain/ParaVision/methods/src/sl_trigMSME/loadMeth.c */
void loadMeth(const char *);
/* /opt/PV6.0.1/prog/curdir/sylvain/ParaVision/methods/src/sl_trigMSME/parsRelations.c */
void ExcPulse1EnumRelation(void);
void ExcPulse1AmplRel(void);
void HandleRFPulseAmplitudes(void);
void ExcPulse1Relation(void);
void ExcPulse1Range(void);
void RefPulse1EnumRelation(void);
void RefPulse1AmplRel(void);
void RefPulse1Relation(void);
void RefPulse1Range(void);
void effTErels(void);
void NAveragesRange(void);
void NAveragesRels(void);
void EffSWhRange(void);
void EffSWhRel(void);
void localInversionRel(void);
void RepetitionSpoilerRel(void);
/* /opt/PV6.0.1/prog/curdir/sylvain/ParaVision/methods/src/sl_trigMSME/backbone.c */
void backbone(void);
void UpdateSequenceTiming(void);
void UpdateRepetitionTime(void);
void UpdateTotalTime(void);
void UpdateGeometryMinima(double *, double *);
void UpdateReadSliceGradients(void);
void UpdatePhaseGradients(void);
void UpdateEchoSpoilers(void);
void UpdateFrequencyOffsets(void);
void UpdateRFPulses(void);
void ControlGradientLimits(YesNo);
void UpdateEchoTime(double *, double *);
double minLoopRepetitionTime(void);
void UpdateMultiEchoes(void);
void calcEffTE(int, double, double, const int *, double *);
void CreateSegmentList(void);
void CreateDelayListe(void);
/* /opt/PV6.0.1/prog/curdir/sylvain/ParaVision/methods/src/sl_trigMSME/BaseLevelRelations.c */
void SetBaseLevelParam(void);
void SetBasicParameters(void);
void SetFrequencyParameters(void);
void SetGradientParameters(void);
void SetInfoParameters(void);
void SetMachineParameters(void);
void SetPpgParameters(void);
void printTiming(void);
/* /opt/PV6.0.1/prog/curdir/sylvain/ParaVision/methods/src/sl_trigMSME/RecoRelations.c */
void SetRecoParam(void);
void RecoDerive(void);
