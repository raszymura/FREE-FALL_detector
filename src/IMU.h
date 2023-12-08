#pragma once

struct IMUData {  
    double ax, ay, az;  // Accelerometer data
    double gx, gy, gz;  // Gyroscope data
};

struct IMURegisters {
    int samplingRate;        // Sampling rate in [Hz]
    int accelerometerRange;  // Accelerometer measurement range in [g] ( 1g = 9.80665 m/(s^2)) )
    int gyroscopeRange;      // Gyroscope measurement range in [dps]
};

/*-------From datasheet
Output Data Rate (ODR) - (aka “sampling rate”) is the rate at which a sensor obtains new measurements,
or samples. ODR is measured in number of samples per second (Hz).

Full Scale Range (FSR) - is associated with the range of values that can be measured for a given sensor and allows 
the application developer to trade-off measurement precision for larger ranges of detection. 

The full-scale range of the gyro sensor may be digitally programmed to:
±250, ±500, ±1000, ±2000 degrees per second (dps).

The full-scale range of the accelerometers sensor may be adjusted to:
±2g, ±4g, ±8g and ±16g.


FIFO
The ICM-42670-P contains up to 2.25Kbyte FIFO register that is accessible via the serial interface. 
Shared SRAM is used for FIFO and APEX features. 
Default configuration of the device provides 1Kbyte FIFO and rest of the SRAM is 
used for APEX. User may disable APEX features to extend FIFO size to 2.25 Kbytes using register field 
APEX_DISABLE in register SENSOR_CONFIG3. 
User can configure the FIFO Data Rate (FDR) to control the rate at which FIFO packets are written to the FIFO. 
Register field FDR_SEL in register FDR_CONFIG (register 0x66h in Bank MREG1) provides FDR control, based on 
settings for FIFO packet rate decimation factor. User must disable sensors when initializing FDR_SEL value or 
making changes to it.


PACKET STRUCTURE
Figure 9 shows the FIFO packet structures supported in ICM-42670-P. Base data format for gyroscope and 
accelerometer is 16-bits per element. 20-bits data format support is included in one of the packet structures. 
When 20-bits data format is used, gyroscope data consists of 19-bits of actual data and the LSB is always set to 0, 
accelerometer data consists of 18-bits of actual data and the two lowest order bits are always set to 0. When 20-
bits data format is used, the only FSR settings that are operational are ±2000 dps for gyroscope and ±16g for 
accelerometer, even if the FSR selection register settings are configured for other FSR values. The corresponding 
sensitivity scale factor values are 131 LSB/dps for gyroscope and 8192 LSB/g for accelerometer.

I2C
The ICM-42670-P always operates as a slave device when communicating to the system processor, which thus acts 
as the master. SDA and SCL lines typically need pull-up resistors to VDDIO. The maximum bus speed is 1 MHz.

*/