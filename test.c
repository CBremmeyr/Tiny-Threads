/**
 * Kernel.c
 *
 * Author(s): Corbin Bremmeyr, Richard Critchlow
 * Date: 28 July 2020
 *
 * Black-box testing of OS.h functions using standard C assert() macro
 */
#include <assert.h>
#include <stdlib.h>

#include "OS.h"

void test_thread0(void);
void test_thread1(void);

static int thread_run_flag = 0;
static lock_t test_lock = 1;

void test_thread0(void) {

    // This thread should run first
    assert(thread_run_flag == 0);

    // Set flag to show this thread has run
    if(thread_run_flag == 0) {
        thread_run_flag = 1;
        yield();
    }

    while(1) {

        // If true then both threads have run and first thread has regained CPU control
        if(thread_run_flag == 2) {

            // End testing
            exit(0);
        }
    }
}

void test_thread1(void) {

    // Thread0 should run before this thread
    assert(thread_run_flag == 1);

    if(thread_run_flag == 1) {
        thread_run_flag = 2;
    }

    while(1) { }
}

void test_thread2(void) {
    while(1);
}


void test_OS_Init(void) {

    OS_Init();

    // Check side effects of OS_Init set correct register values
    assert(SysTick->CTRL == (uint32_t)0x06);
    assert(SCB -> SHP[1] == (SCB -> SHP[1] & 0x00FFFFFF) | 0xE0000000);
}

void test_AddThreads() {

    // No side effects that can be check outside the scope of the library
    assert(OS_AddThread(test_thread0) == 1);
    assert(OS_AddThread(test_thread1) == 1);
    assert(OS_AddThread(test_thread2) == 1);
    assert(OS_AddThread(NULL) == 0);
}

void test_OS_Launch() {

    OS_Launch(TIME_2MS);    // Control should be transfered to test_threadX() functions

    // See test_thread0() and test_thread1() for rest of test
}

void test_Lock_Init(void) {
    Lock_Init(&test_lock);
    assert(test_lock == 0);
}

void test_Lock_Acquire_Release(void) {

    // Acquire lock should succeed on first call
    assert(Lock_Acquire(&test_lock) == 1);

    // Should fail since already locked
    assert(Lock_Acquire(&test_lock) == 0);

    // Open lock
    Lock_Release(&test_lock);

    // Should be able to lock again
    assert(Lock_Acquire(&test_lock) == 1);
    Lock_Release(&test_lock);
}

// ===== Run all tests =====
void test_run(void) {

    // Test resource locking
    test_Lock_Init();
    test_Lock_Acquire_Release();

    // Test threads
    test_OS_Init();
    test_AddThreads();
    test_OS_Launch();
}
