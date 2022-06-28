#include "MCSStruct.h"

PyObject *create_mcs(
    const MCSStruct *const mcs_struct,
    const int32_t *const mcsevent_struct,
    const EventStruct *const event_struct,
    const BEEventStruct *const beevent_struct,
    const CCFEventStruct *const ccfevent_struct,
    const MODEventStruct *const modevent_struct,
    const char *encoding,
    const uint_fast32_t start,
    const uint_fast32_t end,
    const int with_header,
    const int mod_expand)
{
    PyObject *col_obj = PyTuple_New(end-start+with_header);
    uint_fast8_t max_mcs_len = 1;
    for (uint_fast32_t row = start; row < end; row++)
    {
        MCSStruct mcs = mcs_struct[row];
        const uint_fast32_t column_count = mcs.LastEvent - mcs.FirstEvent + 1;
        max_mcs_len = MAX(max_mcs_len, column_count);
        PyObject *row_obj = PyTuple_New(column_count + 1);

        PyTuple_SET_ITEM(row_obj, 0, Py_BuildValue("d", mcs.Mean));

        for (uint_fast32_t column = 0; column < column_count; column++)
        {
            // Address to event struct. If negative then not event
            const int32_t e9 = mcsevent_struct[mcs.FirstEvent + column];
            EventStruct event = event_struct[abs(e9)];

            const uint32_t event_index = event.Index;
            const EventType event_type = event.EventType;

            const char *name;
            switch (event_type)
            {
            case BASIC_EVENT:
                name = beevent_struct[event_index].Name;
                break;
            case CCF_EVENT:
                name = ccfevent_struct[event_index].Name;
                break;
            case MOD_EVENT:
                name = modevent_struct[event_index].Name;
                break;
            default:
                PyErr_Format(PyExc_RuntimeError, "Can't read event, undefine event type '%u' in (%u, %u)", event_type, row, column+1);
                return NULL;
            }

            const Py_ssize_t len = trim(name, MAX_ID_LEN);
            PyObject *name_obj;

            // Test on non negative event
            if  (abs(e9)+e9>0)
            {
                name_obj = PyUnicode_Decode(name, len, encoding, NULL);
            }
            else
            {
                char neg_name[MAX_ID_LEN+1];
                neg_name[0]='-';
                strncpy(&neg_name[1], name, len); 
                name_obj = PyUnicode_Decode(neg_name, len+1, encoding, NULL);
            }
            PyTuple_SET_ITEM(row_obj, column + 1, name_obj);
            //PyTuple_SET_ITEM(row_obj, column + 1, Py_BuildValue("s#", name, len));
        }

        PyTuple_SET_ITEM(col_obj, row+with_header-start, row_obj);
    }
    if (with_header)
    {
        PyObject *header_obj = PyTuple_New(max_mcs_len + 1);
        PyTuple_SET_ITEM(header_obj, 0, Py_BuildValue("s", "Mean"));
        for (uint_fast8_t i = 1; i < max_mcs_len + 1; i++)
        {
            char s[10];
            snprintf(s, sizeof(s), "Event %u", i);
            PyTuple_SET_ITEM(header_obj, i, Py_BuildValue("s", s));
        }
        PyTuple_SET_ITEM(col_obj, 0, header_obj);
    }

    return col_obj;
}