#include <console/console.h>
#include <device/device.h>
#include <device/device.h>
#include <device/pci.h>
#include <string.h>
#include <cpu/cpu.h>
#include <cpu/x86/mtrr.h>
#include <cpu/x86/msr.h>
#include <cpu/x86/lapic.h>
#include <cpu/intel/microcode.h>
#include <cpu/x86/cache.h>
#include <cpu/x86/mtrr.h>

static uint32_t microcode_updates[] = {
	/*  Dummy terminator  */
        0x0, 0x0, 0x0, 0x0,
        0x0, 0x0, 0x0, 0x0,
        0x0, 0x0, 0x0, 0x0,
        0x0, 0x0, 0x0, 0x0,
};


static void model_69x_init(device_t dev)
{
	/* Turn on caching if we haven't already */
	x86_enable_cache();
	x86_mtrr_check();
	
	/* Update the microcode */
	intel_update_microcode(microcode_updates);

	/* Enable the local cpu apics */
	setup_lapic();
};

static struct device_operations cpu_dev_ops = {
	.init     = model_69x_init,
};
static struct cpu_device_id cpu_table[] = {
#if 0
	{ X86_VENDOR_INTEL, 0x0695 }, /* Pentium M */
#endif
	{ 0, 0 },
};

static struct cpu_driver driver __cpu_driver = {
	.ops      = &cpu_dev_ops,
	.id_table = cpu_table,
};
