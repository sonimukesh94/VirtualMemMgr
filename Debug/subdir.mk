################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../AbsPageReplacement.cpp \
../Client.cpp \
../MainMemory.cpp \
../MemoryManager.cpp \
../Page.cpp \
../PageTable.cpp \
../SecondaryMemory.cpp 

OBJS += \
./AbsPageReplacement.o \
./Client.o \
./MainMemory.o \
./MemoryManager.o \
./Page.o \
./PageTable.o \
./SecondaryMemory.o 

CPP_DEPS += \
./AbsPageReplacement.d \
./Client.d \
./MainMemory.d \
./MemoryManager.d \
./Page.d \
./PageTable.d \
./SecondaryMemory.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


