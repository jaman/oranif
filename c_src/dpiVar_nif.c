#include "dpiVar_nif.h"

ErlNifResourceType *dpiVar_type;

void dpiVar_res_dtor(ErlNifEnv *env, void *resource)
{
    TRACE;

    L("dpiVar destroyed\r\n");
}

DPI_NIF_FUN(dpiVar_setNumElementsInArray)
{
    CHECK_ARGCOUNT(2);

    dpiVar_res *vRes = NULL;
    uint32_t numElements;

    if ((!enif_get_resource(env, argv[0], dpiVar_type, &vRes)))
        return BADARG_EXCEPTION(0, "resource var");
    if (!enif_get_int(env, argv[1], &numElements))
        return BADARG_EXCEPTION(1, "uint numElements");

    RAISE_EXCEPTION_ON_DPI_ERROR(
        dpiVar_setNumElementsInArray(vRes->var, numElements));

    return ATOM_OK;
}

DPI_NIF_FUN(dpiVar_setFromBytes)
{
    CHECK_ARGCOUNT(3);

    dpiVar_res *vRes = NULL;
    ErlNifBinary value;
    uint32_t pos;

    if ((!enif_get_resource(env, argv[0], dpiVar_type, &vRes)))
        return BADARG_EXCEPTION(0, "resource vat");
    if (!enif_get_int(env, argv[1], &pos))
        return BADARG_EXCEPTION(1, "uint pos");
    if (!enif_inspect_binary(env, argv[2], &value))
        return BADARG_EXCEPTION(2, "binary/string value");

    RAISE_EXCEPTION_ON_DPI_ERROR(
        dpiVar_setFromBytes(vRes->var, pos, value.data, value.size));

    return ATOM_OK;
}

DPI_NIF_FUN(dpiVar_release)
{
    CHECK_ARGCOUNT(1);

    dpiVar_res *vRes = NULL;

    if ((!enif_get_resource(env, argv[0], dpiVar_type, &vRes)))
        return BADARG_EXCEPTION(0, "resource var");

    return ATOM_OK;
}

UNIMPLEMENTED(dpiVar_addRef);
UNIMPLEMENTED(dpiVar_copyData);
UNIMPLEMENTED(dpiVar_getNumElementsInArray);
UNIMPLEMENTED(dpiVar_getReturnedData);
UNIMPLEMENTED(dpiVar_getSizeInBytes);
UNIMPLEMENTED(dpiVar_setFromLob);
UNIMPLEMENTED(dpiVar_setFromObject);
UNIMPLEMENTED(dpiVar_setFromRowid);
UNIMPLEMENTED(dpiVar_setFromStmt);