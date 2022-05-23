#ifndef RESSUMMARYMISCSTRUCT
#define RESSUMMARYMISCSTRUCT

#include <Python.h>
#include <fcntl.h>
 
typedef struct 
{
    uint32_t iDummy[9];
    double fDummy[9];
    double cDummy[9][20];
}__attribute__ ((__packed__)) ResSummaryMiscStruct;

extern PyTypeObject ResSummaryMiscType;
extern PyStructSequence_Desc ResSummaryMiscType_desc;

PyObject *create_ResSummaryMisc(ResSummaryMiscStruct *misc_struct);



#endif /* RESSUMMARYMISCSTRUCT */
