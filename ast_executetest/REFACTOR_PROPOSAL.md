# Header Slimming & Static Function Refactor Proposal

## Executive Summary
Analysis shows **11 debug functions** can be made static (100% of debug.c exports).
This will reduce `execution.h` from **132 lines to ~105 lines** (~20% reduction).

---

## Call Graph Analysis

### 🔴 GLOBAL HUBS (Must stay in headers)

#### Core Execution Flow
- `execute_ast()` ← test_main.c, test_simple.c
- `execute_command()` ← children.c
- `execute_parent_builtin()` ← exec_ast.c
- `free_ast_root()` ← builtins.c, exec_utils.c

#### Child Process Management
- `only_child()` ← exec_ast.c
- `first_child()` ← exec_ast.c
- `last_child()` ← exec_ast.c
- `middle_child()` ← exec_ast.c

#### Builtin Commands (all called from exec_cmd.c)
- `ft_cd()`, `ft_exit()`, `ft_echo()`, `ft_pwd()`
- `ft_env()`, `ft_export()`, `ft_unset()`

#### Environment Management
- `initenv()` ← test_simple.c
- `addenv()` ← builtins.c, builtins_more.c, exec_ast.c
- `rmenv()` ← builtins.c, builtins_more.c
- `fetchenv()` ← builtins.c, builtins_more.c, exec_cmd.c
- `get_sorted_env()` ← builtins_more.c

#### Utilities
- `is_builtin()` ← exec_ast.c, exec_cmd.c
- `free_array()` ← environment.c, exec_cmd.c
- `count_array()` ← environment.c
- `ft_error()` ← builtins.c, children.c, exec_ast.c, exec_cmd.c, redirection.c

#### Redirection
- `setup_redirections()` ← children.c

#### Path Resolution
- `get_path()` ← exec_cmd.c (called internally)

#### Test Utilities
- `free_ast()` ← exec_ast.c, test_main.c, test_simple.c
- `create_test_ast()` ← test_main.c (in ast.h)

---

### 🟢 STATIC CANDIDATES (Can be internalized)

#### Debug Functions (debug.c) - **ALL 11 UNUSED EXTERNALLY**
- `dbg_print()` - only local
- `dbg_print_ast()` - only local
- `dbg_trace_cmd()` - only local
- `dbg_trace_pipe()` - only local
- `dbg_trace_fds()` - only local
- `dbg_trace_child()` - only local
- `dbg_trace_path()` - only local
- `dbg_trace_env()` - only local
- `dbg_toggle()` - only local
- `dbg_enable()` - only local
- `dbg_disable()` - only local

**Note:** Debug functions are currently not referenced anywhere! They appear to be scaffolding for future use or were orphaned during cleanup.

---

## Proposed Changes

### Phase 1: Remove Orphaned Debug Prototypes ✅
**Impact:** Remove 11 prototypes from `execution.h` (lines 119-129)

All debug functions are unused. Options:
1. **Make them static** (keep for future debugging)
2. **Delete them entirely** (clean slate)
3. **Comment them out** (middle ground)

**Recommendation:** Make static + add comment explaining they're available for debugging

### Phase 2: No Further Static Opportunities 🔒
All other non-static functions are legitimately used across files and serve as necessary API hubs.

### Phase 3: Optional File Reorganization
Consider merging small related files:
- `builtins.c` + `builtins_more.c` → single `builtins.c`
- Keep `children.c`, `environment.c`, `redirection.c` separate (cohesive units)

---

## Implementation Plan

### 1️⃣ Make debug functions static
```c
// In debug.c - add static to all 11 function definitions
static void dbg_print(char *msg) { ... }
static void dbg_print_ast(t_ast *ast, int depth) { ... }
// ... etc
```

### 2️⃣ Remove from execution.h
Delete lines 118-129 (debug function prototypes), add single comment:
```c
/* Debug functions available in debug.c (all static - enable as needed) */
```

### 3️⃣ Optional: Add usage comment in debug.c
```c
/*
** Debug utility functions - currently static/unused.
** Remove 'static' keyword and add prototype to execution.h to enable.
*/
```

---

## Final Header Size
**Before:** 132 lines
**After:** ~105 lines
**Reduction:** 27 lines (20%)

---

## Call Graph Summary

```
execute_ast (HUB)
├─→ recursive_exec (static)
│   ├─→ only_child (HUB)
│   ├─→ first_child (HUB)
│   ├─→ last_child (HUB)
│   └─→ middle_child (HUB)
│       └─→ setup_redirections (HUB)
│           └─→ redirect (static)
│       └─→ execute_command (HUB)
│           ├─→ get_path (internal)
│           │   └─→ get_path2 (static)
│           ├─→ is_builtin (HUB)
│           └─→ [all 7 builtins] (HUB)
│               └─→ addenv/rmenv/fetchenv (HUB)
├─→ execute_parent_builtin (HUB)
└─→ wait_for_children (static)
    └─→ addenv (HUB)

ft_error (UNIVERSAL HUB - called from everywhere)
free_array (UTILITY HUB)
count_array (UTILITY HUB)
```

---

## Notes
- `get_path()` is exported but only used in exec_cmd.c - could be static later
- Test files (test_*.c) will be removed in production, affecting some dependencies
- All internal helpers are already properly static
- Environment management is tightly cohesive and well-encapsulated
