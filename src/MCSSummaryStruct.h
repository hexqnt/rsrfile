#ifndef MCSSUMMARYSTRUCT
#define MCSSUMMARYSTRUCT

#include <Python.h>
#include <fcntl.h>
 
#include "LargeNumStruct.h"
#include "common.h"

typedef struct  
{
    char DateTime[20];
    uint16_t InputFormat;
    uint16_t AcaseType;
    uint32_t AcaseSpec1_rsat;
    uint32_t AcaseSpec1_rsatexe;
    uint32_t AcaseSpec1_rsmisc;
    uint32_t AcaseSpec1_rsuit;
    uint32_t AcaseSpec1_rsmcs;
    uint32_t AcaseSpec2;
    uint32_t BCSetUsed;
    uint16_t CalcType;
    double Time;
    uint16_t CutOffType;
    double AbsCutOff;
    double RelCutOff;
    uint16_t Approx;
    uint16_t IncludeCCF;
    uint16_t NegationHandling;
    double SaveCutoff;
    uint32_t MaxSavedModMCS;
    uint32_t MaxSavedDemodMCS;
    uint32_t Events;
    uint32_t BEEvents;
    uint32_t CCFEvents;
    uint32_t Gates;
    uint32_t PrimaryEvents;
    uint32_t ModEvents;
    uint32_t ModBEEvents;
    uint32_t ModCCFEvents;
    uint32_t ModGates;
    uint32_t ModPrimaryEvents;
    uint32_t Modules;
    uint32_t ModChildren;
    LargeNumStruct BICSMod;
    LargeNumStruct BICSDemod;
    uint32_t MCSMod;
    LargeNumStruct TotDemodMCS;
    uint32_t MCSDemod;
    uint32_t MCSModSaved;
    uint32_t MCSDemodSaved;
    double fQ[4];
    double QBestApprox;
    double fW[4];
    double WBestApprox;
    double TruncErrorMod;
    double TruncErrorDemod;
    double TruncErrorTot;
    double UsedCutoffDemod;
    double UsedCutoffMod;
    double RunTimeTot;
    double RunTimeMCS;
}__attribute__ ((__packed__)) MCSSummaryStruct;

extern PyTypeObject MCSSummaryType;
extern PyStructSequence_Desc MCSSummaryType_desc;

PyObject *create_MCSSummary(MCSSummaryStruct *mcs_struct);

#endif /* MCSSUMMARYSTRUCT */
