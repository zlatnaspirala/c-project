
namespace getDevices
{

    using System;
    using System.Management;

    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
            Console.WriteLine("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");

            ManagementObjectSearcher mos = new ManagementObjectSearcher("select * from Win32_SoundDevice");
            foreach (ManagementObject soundDevice in mos.Get())
            {
                String sDeviceId = soundDevice.GetPropertyValue("DeviceId").ToString();
                String sDeviceName = soundDevice.GetPropertyValue("Name").ToString();
                String sDeviceStatus = soundDevice.GetPropertyValue("Status").ToString();
                Console.WriteLine("Device Name = {0} - Device Id = {1} - Status = {2}", sDeviceName, sDeviceId, sDeviceStatus);
            }
            ManagementObjectSearcher mos2 = new ManagementObjectSearcher("select * from Win32_VideoController");
            foreach (ManagementObject videoDevice in mos2.Get())
            {
                String sDeviceId = videoDevice.GetPropertyValue("DeviceId").ToString();
                String sDeviceName = videoDevice.GetPropertyValue("Name").ToString();
                String sDeviceStatus = videoDevice.GetPropertyValue("Status").ToString();
                Console.WriteLine("Device Name = {0} - Device Id = {1} - Status = {2}", sDeviceName, sDeviceId, sDeviceStatus);
            }

            Console.WriteLine("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
            Console.WriteLine("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
        }
    }

    }

