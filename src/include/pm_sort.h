#ifndef __PM_SORT_H__
#define __PM_SORT_H__

#include <stddef.h>

/**********************************************************************
 * FUNCTION PROTOTYPE DEFINITIONS.                                    *
 **********************************************************************/
typedef int  pmSortCmp_t (void *obj1, void *obj2);
typedef void pmSortCopy_t (void *obj1, void *obj2);

typedef pmSortCmp_t   *pmSortCmp_p;
typedef pmSortCopy_t  *pmSortCopy_p;

/**********************************************************************
 * GLOBAL FUNCTION DECLARATIONS.                                      *
 **********************************************************************/
void pmSort (void          *objects,
             int           nObjects,
             size_t        objSize,
             pmSortCmp_p   cmp,
             pmSortCopy_p  copy,
             void          *sortedObjs);


#endif /* __PM_SORT_H__ */
