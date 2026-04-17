#ifndef PES_H
#define PES_H

#include <stdint.h>   // for uint8_t
#include <stddef.h>   // for size_t
#include <stdlib.h>   // for getenv

#define HASH_SIZE 32
#define HASH_HEX_SIZE 64
#define PES_DIR ".pes"
#define OBJECTS_DIR ".pes/objects"
#define REFS_DIR ".pes/refs/heads"
#define INDEX_FILE ".pes/index"
#define HEAD_FILE ".pes/HEAD"

// ─── Object Types ─────────────────────────────────────────

typedef enum {
    OBJ_BLOB,
    OBJ_TREE,
    OBJ_COMMIT
} ObjectType;

// ─── Object Identifier ───────────────────────────────────

typedef struct {
    uint8_t hash[HASH_SIZE];
} ObjectID;

// ✅ ADD THESE HERE
int object_write(ObjectType type, const void *data, size_t len, ObjectID *out_id);
int object_read(const ObjectID *id, ObjectType *type, void **data, size_t *len);

// ─── Utility Functions ───────────────────────────────────

void hash_to_hex(const ObjectID *id, char *hex_out);
int hex_to_hash(const char *hex, ObjectID *id_out);

// ─── Author ──────────────────────────────────────────────

#define DEFAULT_AUTHOR "PES User <pes@localhost>"

static inline const char* pes_author(void) {
    const char *env = getenv("PES_AUTHOR");
    return (env && env[0]) ? env : DEFAULT_AUTHOR;
}

#endif // PES_H
