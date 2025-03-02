---@diagnostic disable: undefined-global, undefined-field
-- 添加构建规则
add_rules("mode.debug", "mode.release")

-- 设置语言标准
set_languages("c99", "c++11")

-- 自定义工具链
toolchain("arm-none-eabi")
    -- 标记为自定义独立工具链
    set_kind("standalone")
    -- 定义交叉编译工具链地址
    set_sdkdir("../arm-none-eabi")
toolchain_end()

-- 生成固件
target("firmware")
	-- 设置生成类型
    set_kind("binary")

    -- 设置生成文件名称
    set_basename("firmware.elf")
	
    -- 设置使用的交叉编译工具链
    set_toolchains("arm-none-eabi")

    -- 设置平台 表示交叉编译程序
    set_plat("cross")
	
    -- 设置架构
    set_arch("m3")
	
	-- 添加宏定义
	add_defines("USE_STDPERIPH_DRIVER","STM32F10X_MD")
	
	-- 添加头文件
    add_includedirs("USER")
	add_includedirs("STDLIB/inc")
	add_includedirs("CMSIS/CoreSupport")
	add_includedirs("CMSIS/DeviceSupport")
    add_includedirs("BSP/spi2c")
	
	-- 添加源文件和汇编文件
    add_files("USER/*.c")
	add_files("STDLIB/**.c")
	add_files("CMSIS/**.c")
	add_files("CMSIS/DeviceSupport/startup/startup_stm32f10x_md.s")
    add_files("BSP/spi2c/*.c")
	
	-- 添加链接库
	add_links("c", "m", "nosys", "rdimon")
	
	-- 设置编译器选项
    add_cflags(
        "-Og",
        "-mcpu=cortex-m3",
        "-mthumb",
        "-Wall",
        "-fdata-sections",
        "-ffunction-sections",
        "-g -gdwarf-2",
        {force = true}
    )
	
	-- 设置汇编器选项
    add_asflags(
        "-Og",
        "-mcpu=cortex-m3",
        "-mthumb",
		"-x assembler-with-cpp",
        "-Wall",
        "-fdata-sections", 
        "-ffunction-sections",
        "-g -gdwarf-2",
        {force = true}
    )
	
	-- 设置链接器选项(-T选项根据芯片填写链接脚本)
    add_ldflags(
        "-Og",
        "-mcpu=cortex-m3",
        "-T$(projectdir)/USER/STM32F103C8Tx_FLASH.ld",
        "-Wl,--gc-sections",
        "--specs=nosys.specs",
        "-u _printf_float",  
        {force = true}
    )

    -- 格式转换与打印
    after_build(
        function(target)
        print("Compile finished!!!")
        print("Next, generate hex and bin files.")
        os.exec("../arm-none-eabi/bin/arm-none-eabi-objcopy -O ihex $(buildir)/cross/m3/$(mode)/firmware.elf $(buildir)/cross/m3/$(mode)/firmware.hex")
        os.exec("../arm-none-eabi/bin/arm-none-eabi-objcopy -O binary -S $(buildir)/cross/m3/$(mode)/firmware.elf $(buildir)/cross/m3/$(mode)/firmware.bin")
        print("Generate hex and bin files ok!!!")

        print(" ");
        print("********************program size*****************************")
        os.exec("../arm-none-eabi/bin/arm-none-eabi-size $(buildir)/cross/m3/$(mode)/firmware.elf")
    end)
target_end()


-- 烧录
task("flash")
    on_run(function()
        os.exec([[openocd -f interface/cmsis-dap.cfg -f target/stm32f1x.cfg -c "program $(buildir)/cross/m3/release/firmware.hex verify reset exit"]])
    end)
    set_menu {
        -- usage
        usage = "xmake flash",
        -- description
        description = "Flash firmware.bin to target board.",
        -- options
        options = {}
    }
task_end()