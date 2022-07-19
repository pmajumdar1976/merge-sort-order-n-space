#include "test_common.h"
#include <pm_sort.h>

/**********************************************************************
 * STATIC FUNCTION DECLARATIONS.                                      *
 **********************************************************************/
static pmSortCmp_t  __UTUnsignedIntAscendingCMP;
static pmSortCmp_t  __UTUnsignedIntDescendingCMP;
static pmSortCopy_t __UTUnsignedIntCopy;
static void pmSortTestBasicEvenCount (void **state);
static void pmSortTestAllEquals (void **state);
static void pmSortTestDescendingLongArray (void **state);

/**********************************************************************
 * GLOBAL FUNCTION DEFINITIONS.                                       *
 **********************************************************************/
int
main (void)
{
    const char               *groupName = "pmsort";
    const struct CMUnitTest  tests[]    = {
        cmocka_unit_test (pmSortTestBasicEvenCount),
        cmocka_unit_test (pmSortTestAllEquals),
        cmocka_unit_test (pmSortTestDescendingLongArray),
    };

    return cmocka_run_group_tests_name (groupName, tests, NULL, NULL);
}

/**********************************************************************
 * STATIC FUNCTION DEFINITIONS.                                       *
 **********************************************************************/
static int
__UTUnsignedIntAscendingCMP (void *obj1, void *obj2)
{
    return (int) ((*(unsigned int *) obj1) - (*(unsigned int *) obj2));
}

static int
__UTUnsignedIntDescendingCMP (void *obj1, void *obj2)
{
    return (int) ((*(unsigned int *) obj2) - (*(unsigned int *) obj1));
}

static void
__UTUnsignedIntCopy (void *dst, void *src)
{
    *(unsigned int *) dst = *(unsigned int *) src;
}

static void
pmSortTestBasicEvenCount (void **state)
{
    unsigned int    input [] = {91, 23, 45, 37, 69, 58, 83, 90, 7, 41};
    unsigned int    sorted [sizeof (input) / sizeof (unsigned int)] = {0};

#if 0
    printf ("Input array: {%u, %u, %u, %u, %u, %u, %u, %u, %u, %u}\n",
            input[0], input[1], input[2], input[3], input[4],
            input[5], input[6], input[7], input[8], input[9]);
#endif /* 0 */

    pmSort (input,
            sizeof (input) / sizeof (unsigned int),
            sizeof (unsigned int),
            __UTUnsignedIntAscendingCMP,
            __UTUnsignedIntCopy,
            sorted);

#if 0
    printf ("Sorted array: {%u, %u, %u, %u, %u, %u, %u, %u, %u, %u}\n",
            sorted[0], sorted[1], sorted[2], sorted[3], sorted[4],
            sorted[5], sorted[6], sorted[7], sorted[8], sorted[9]);
#endif /* 0 */

    assert_true (sorted[0] == 7  && sorted[1] == 23 && sorted[2] == 37 &&
                 sorted[3] == 41 && sorted[4] == 45 && sorted[5] == 58 &&
                 sorted[6] == 69 && sorted[7] == 83 && sorted[8] == 90 &&
                 sorted[9] == 91);
}

static void
pmSortTestAllEquals (void **state)
{
    unsigned int    input [] = {232, 232, 232, 232, 232, 232, 232, 232, 232, 232, 232};
    unsigned int    sorted [sizeof (input) / sizeof (unsigned int)] = {0};

#if 0
    printf ("Input array: {%u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u}\n",
            input[0], input[1], input[2], input[3], input[4], input[5],
            input[6], input[7], input[8], input[9], input[10]);
#endif /* 0 */

    pmSort (input,
            sizeof (input) / sizeof (unsigned int),
            sizeof (unsigned int),
            __UTUnsignedIntAscendingCMP,
            __UTUnsignedIntCopy,
            sorted);

#if 0
    printf ("Sorted array: {%u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u}\n",
            sorted[0], sorted[1], sorted[2], sorted[3], sorted[4], sorted[5],
            sorted[6], sorted[7], sorted[8], sorted[9], sorted[10]);
#endif /* 0 */

    assert_true (sorted[0] == 232 && sorted[1] == 232 && sorted[2] == 232 &&
                 sorted[3] == 232 && sorted[4] == 232 && sorted[5] == 232 &&
                 sorted[6] == 232 && sorted[7] == 232 && sorted[8] == 232 &&
                 sorted[9] == 232 && sorted [10] == 232);
}

static void
pmSortTestDescendingLongArray (void **state)
{
    unsigned int    input [] = { 11,  25,  39,  42,  43,  59,  66,  88,  89,  93, 117,
                                 10, 125,  38, 142,  42, 159,  65, 188,  88, 193, 116,
                                111,  24, 139,  41, 143,  58, 166,  87, 189,  92, 217,
                                  9, 225,  37, 242,  41, 259,  64, 288,  87, 293, 115};
    unsigned int    sorted [sizeof (input) / sizeof (unsigned int)] = {0};

#if 0
    printf ("Input array: {%u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u,\n"
            "              %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u,\n"
            "              %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u,\n"
            "              %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u}\n",
            input[0],  input[1],  input[2],  input[3],  input[4],  input[5],
            input[6],  input[7],  input[8],  input[9],  input[10], input[11],
            input[12], input[13], input[14], input[15], input[16], input[17],
            input[18], input[19], input[20], input[21], input[22], input[23],
            input[24], input[25], input[26], input[27], input[28], input[29],
            input[30], input[31], input[32], input[33], input[34], input[35],
            input[36], input[37], input[38], input[39], input[40], input[41],
            input[42], input[43]);
#endif /* 0 */

    pmSort (input,
            sizeof (input) / sizeof (unsigned int),
            sizeof (unsigned int),
            __UTUnsignedIntDescendingCMP,
            __UTUnsignedIntCopy,
            sorted);

#if 0
    printf ("Sorted array: {%u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u,\n"
            "               %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u,\n"
            "               %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u,\n"
            "               %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u}\n",
            sorted[0],  sorted[1],  sorted[2],  sorted[3],  sorted[4],  sorted[5],
            sorted[6],  sorted[7],  sorted[8],  sorted[9],  sorted[10], sorted[11],
            sorted[12], sorted[13], sorted[14], sorted[15], sorted[16], sorted[17],
            sorted[18], sorted[19], sorted[20], sorted[21], sorted[22], sorted[23],
            sorted[24], sorted[25], sorted[26], sorted[27], sorted[28], sorted[29],
            sorted[30], sorted[31], sorted[32], sorted[33], sorted[34], sorted[35],
            sorted[36], sorted[37], sorted[38], sorted[39], sorted[40], sorted[41],
            sorted[42], sorted[43]);
#endif /* 0 */

    assert_true (sorted[0]  == 293 && sorted[1]  == 288 && sorted[2]  == 259 &&
                 sorted[3]  == 242 && sorted[4]  == 225 && sorted[5]  == 217 &&
                 sorted[6]  == 193 && sorted[7]  == 189 && sorted[8]  == 188 &&
                 sorted[9]  == 166 && sorted[10] == 159 && sorted[11] == 143 &&
                 sorted[12] == 142 && sorted[13] == 139 && sorted[14] == 125 &&
                 sorted[15] == 117 && sorted[16] == 116 && sorted[17] == 115 &&
                 sorted[18] == 111 && sorted[19] ==  93 && sorted[20] ==  92 &&
                 sorted[21] ==  89 && sorted[22] ==  88 && sorted[23] ==  88 &&
                 sorted[24] ==  87 && sorted[25] ==  87 && sorted[26] ==  66 &&
                 sorted[27] ==  65 && sorted[28] ==  64 && sorted[29] ==  59 &&
                 sorted[30] ==  58 && sorted[31] ==  43 && sorted[32] ==  42 &&
                 sorted[33] ==  42 && sorted[34] ==  41 && sorted[35] ==  41 &&
                 sorted[36] ==  39 && sorted[37] ==  38 && sorted[38] ==  37 &&
                 sorted[39] ==  25 && sorted[40] ==  24 && sorted[41] ==  11 &&
                 sorted[42] ==  10 && sorted[43] ==   9);
}
