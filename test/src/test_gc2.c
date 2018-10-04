#include "greatest.h"

#include "gc.h"


AllocationList* alloc_list;

static void allocation_list_setup(void* data) {

}

static void allocation_list_teardown(void* data) {

}
TEST allocation_list_head_null() {
	init_allocation_list(alloc_list);
	ASSERT(NULL == list.head);
	PASS();
}


static void setup_cb(void *data) {
	printf("setup callback for each test case\n");
}

static void teardown_cb(void *data) {
	printf("teardown callback for each test case\n");
}

SUITE(allocation_list) {
	SET_SETUP(allocation_list_setup, &alloc_list);
	SET_TEARDOWN(allocation_list_teardown, &alloc_list);

	RUN_TEST(allocation_list_head_null);
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
	GREATEST_MAIN_BEGIN();

	RUN_SUITE(allocation_list);

	GREATEST_MAIN_END();
}
