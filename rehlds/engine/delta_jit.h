#pragma once

#include "maintypes.h"

#define DELTAJIT_MAX_BLOCKS 32
#define DELTAJIT_MAX_FIELDS 56

struct deltajit_field {
	unsigned int id;
	unsigned int offset;
	unsigned int length;
	int type;
	unsigned int numBlocks;
};

struct deltajit_memblock_field {
	deltajit_field* field;
	uint16 mask;
	bool first;
	bool last;
};

struct deltajit_memblock {
	unsigned int numFields;
	deltajit_memblock_field fields[24];
};

struct deltajit_memblock_itr_t {
	int memblockId;
	deltajit_memblock* memblock;
	int prefetchBlockId;
};

struct deltajitdata_t {
	unsigned int numblocks;
	deltajit_memblock blocks[DELTAJIT_MAX_BLOCKS];

	unsigned int numFields;
	deltajit_field fields[DELTAJIT_MAX_FIELDS];

	unsigned int numItrBlocks;
	deltajit_memblock_itr_t itrBlocks[DELTAJIT_MAX_BLOCKS];
};

enum deltajit_marked_count_type_t {
	DJ_M_DONT_COUNT,
	DJ_M_CHECK,
	//DJ_M_COUNT, //not implemented yet
};

class CDeltaJit;

class CDeltaJitRegistry {
private:
#ifndef REHLDS_FIXES
	CStaticMap<void*, CDeltaJit*, 4, 64> m_DeltaToJITMap;
#endif

public:
	CDeltaJitRegistry();
	void RegisterDeltaJit(delta_t* delta, CDeltaJit* deltaJit);
	CDeltaJit* GetJITByDelta(delta_t* delta);
	void CreateAndRegisterDeltaJIT(delta_t* delta);
	void Cleanup();
};

union delta_marked_mask_t {
	uint8 u8[8];
	uint32 u32[2];
	uint64 u64;
};


extern CDeltaJitRegistry g_DeltaJitRegistry;

extern int DELTAJit_Fields_Clear_Mark_Check(unsigned char *from, unsigned char *to, delta_t *pFields);
extern void DELTAJit_SetSendFlagBits(delta_t *pFields, int *bits, int *bytecount);
extern void DELTAJit_SetFieldByIndex(struct delta_s *pFields, int fieldNumber);
extern void DELTAJit_UnsetFieldByIndex(struct delta_s *pFields, int fieldNumber);
extern qboolean DELTAJit_IsFieldMarked(delta_t* pFields, int fieldNumber);