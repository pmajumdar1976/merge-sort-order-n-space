#include <pm_sort.h>

/**********************************************************************
 * STATIC FUNCTION DECLARATIONS.                                      *
 **********************************************************************/
static void __pmSortMergeSortedChunks (unsigned char      *chunk1,
                                       unsigned char      *chunk2,
                                       int                chunk1Size,
                                       int                chunk2Size,
                                       unsigned char      *aux,
                                       size_t             objSize,
                                       pmSortCmp_p        cmp,
                                       pmSortCopy_p       copy);

/**********************************************************************
 * GLOBAL FUNCTION DEFINITIONS.                                       *
 **********************************************************************/
void
pmSort (void          *objects,
        int           nObjects,
        size_t        objSize,
        pmSortCmp_p   cmp,
        pmSortCopy_p  copy,
        void          *sortedObjs)
{
    if (nObjects > 1) {
        int            chunk1Size    = nObjects / 2;
        int            chunk2Size    = nObjects - chunk1Size;
        unsigned char  *chunk1       = objects;
        unsigned char  *chunk2       = chunk1 + (objSize * chunk1Size);
        unsigned char  *sortedChunk1 = sortedObjs;
        unsigned char  *sortedChunk2 = sortedChunk1 + (objSize * chunk1Size);

        pmSort (chunk1, chunk1Size, objSize, cmp, copy, sortedChunk1);
        pmSort (chunk2, chunk2Size, objSize, cmp, copy, sortedChunk2);
        __pmSortMergeSortedChunks (sortedChunk1,
                                   sortedChunk2,
                                   chunk1Size,
                                   chunk2Size,
                                   objects,
                                   objSize,
                                   cmp,
                                   copy);
    }
    else if (nObjects) {
        copy (sortedObjs, objects);
    }
}

/**********************************************************************
 * STATIC FUNCTION DEFINITIONS.                                       *
 **********************************************************************/
static void
__pmSortMergeSortedChunks (unsigned char      *chunk1,
                           unsigned char      *chunk2,
                           int                chunk1Size,
                           int                chunk2Size,
                           unsigned char      *aux,
                           size_t             objSize,
                           pmSortCmp_p        cmp,
                           pmSortCopy_p       copy)
{
    unsigned char   *obj1     = chunk1;
    unsigned char   *obj2     = chunk2;
    unsigned char   *auxStart = aux;
    unsigned int    idx1      = 0;
    unsigned int    idx2      = 0;

    while ((idx1 < chunk1Size) && (idx2 < chunk2Size)) {
        if (aux > auxStart) {
            copy (aux, obj1);
            if (cmp (auxStart, obj2) <= 0) {
                copy (obj1, auxStart);
                auxStart += objSize;
            }
            else {
                copy (obj1, obj2);
                obj2 += objSize;
                ++ idx2;
            }
            aux  += objSize;
        }
        else {
            if (cmp (obj1, obj2) > 0) {
                copy (aux, obj1);
                copy (obj1, obj2);
                aux  += objSize;
                obj2 += objSize;
                ++ idx2;
            }
        }
        ++ idx1;
        obj1 += objSize;
    }
    /* If the first chunk is filled up and sorted */
    if (idx1 >= chunk1Size) {
        /* Time to merge aux data and the rest of the second chunk */
        do {
            if (idx2 >= chunk2Size) {
                /* Chunk2 is empty, just copy the aux data */
                while (auxStart < aux) {
                    copy (obj1, auxStart);
                    auxStart += objSize;
                    obj1     += objSize;
                }
                break;
            }
            if (auxStart >= aux) {
                /* Aux storage is empty, just copy the aux data */
                while (idx2 < chunk2Size) {
                    copy (obj1, obj2);
                    obj2 += objSize;
                    obj1 += objSize;
                    ++ idx2;
                }
                break;
            }
            /* Compare first entry for aux storage and second chunk and mode accordingly */
            if (cmp (auxStart, obj2) <= 0) {
                copy (obj1, auxStart);
                auxStart += objSize;
            }
            else {
                copy (obj1, obj2);
                obj2 += objSize;
                ++ idx2;
            }
            obj1 += objSize;
        } while (1);
    }
    else {
        /* Time to merge aux data and the rest of the first chunk */
        while (auxStart < aux) {
            if (idx1 < chunk1Size) {
                copy (aux, obj1);
                aux += objSize;
                copy (obj1, auxStart);
                auxStart += objSize;
                ++ idx1;
            }
            else {
                copy (obj1, auxStart);
                auxStart += objSize;
            }
            obj1 += objSize;
        }
    }
}
