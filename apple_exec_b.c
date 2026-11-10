// x86Sim: Apple's block variant of sqlite3_exec. macOS's libsqlite3 exports it and update_dyld_sim_shared_cache
// (the iOS simulator runtime's dyld cache builder, run under Darling) imports it.
#include "sqlite3.h"

typedef int (^sqlite3_exec_callback_b)(int, char**, char**);

static int exec_b_trampoline(void* ctx, int ncol, char** values, char** names)
{
	return ((sqlite3_exec_callback_b) ctx)(ncol, values, names);
}

SQLITE_API int sqlite3_exec_b(sqlite3* db, const char* sql, sqlite3_exec_callback_b callback, char** errmsg)
{
	return sqlite3_exec(db, sql, callback ? exec_b_trampoline : 0, (void*) callback, errmsg);
}
