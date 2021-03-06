/*-------------------------------------------------------------------------
 *
 * pg_conversion.h
 *	  definition of the "conversion" system catalog (pg_conversion)
 *
 * Portions Copyright (c) 1996-2019, PostgreSQL Global Development Group
 * Portions Copyright (c) 1994, Regents of the University of California
 *
 * src/include/catalog/pg_conversion.h
 *
 * NOTES
 *	  The Catalog.pm module reads this file and derives schema
 *	  information.
 *
 *-------------------------------------------------------------------------
 */
#ifndef PG_CONVERSION_H
#define PG_CONVERSION_H

#include "catalog/genbki.h"
#include "catalog/pg_conversion_d.h"

#include "catalog/objectaddress.h"

/* ----------------
 *		pg_conversion definition.  cpp turns this into
 *		typedef struct FormData_pg_conversion
 * ----------------
 */
CATALOG(pg_conversion,2607,ConversionRelationId)
{
	/* oid */
	Oid			oid;

	/* name of the conversion */
	NameData	conname;

	/* namespace that the conversion belongs to */
	Oid			connamespace BKI_DEFAULT(PGNSP);

	/* owner of the conversion */
	Oid			conowner BKI_DEFAULT(PGUID);

	/* FOR encoding id */
	int32		conforencoding BKI_LOOKUP(encoding);

	/* TO encoding id */
	int32		contoencoding BKI_LOOKUP(encoding);

	/* OID of the conversion proc */
	regproc		conproc BKI_LOOKUP(pg_proc);

	/* true if this is a default conversion */
	bool		condefault BKI_DEFAULT(t);
} FormData_pg_conversion;

/* GPDB added foreign key definitions for gpcheckcat. */
FOREIGN_KEY(connamespace REFERENCES pg_namespace(oid));
FOREIGN_KEY(conowner REFERENCES pg_authid(oid));
FOREIGN_KEY(conproc REFERENCES pg_proc(oid));

/* ----------------
 *		Form_pg_conversion corresponds to a pointer to a tuple with
 *		the format of pg_conversion relation.
 * ----------------
 */
typedef FormData_pg_conversion *Form_pg_conversion;


extern ObjectAddress ConversionCreate(const char *conname, Oid connamespace,
									  Oid conowner,
									  int32 conforencoding, int32 contoencoding,
									  Oid conproc, bool def);
extern void RemoveConversionById(Oid conversionOid);
extern Oid	FindDefaultConversion(Oid connamespace, int32 for_encoding,
								  int32 to_encoding);

#endif							/* PG_CONVERSION_H */
