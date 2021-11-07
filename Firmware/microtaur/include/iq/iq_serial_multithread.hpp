// Copied from "iq_serial.hpp"
#include "client_communication.hpp"
#include "generic_interface.hpp"
#include "HardwareSerial.h"
#include "ChRt.h"
#include "Arduino.h"

class IqSerialMultithreaded
{
public:
    IqSerialMultithreaded(HardwareSerial &my_serial)
    {
        my_serial_ = &my_serial;
    }

    void begin(unsigned long baud)
    {
        my_serial_->begin(baud);
    }

    void begin()
    {
        begin(115200);
    }
    uint8_t get_waiting(){ return communication_length;}

    void set(ClientEntryVoid entry)
    {
        entry.set(com_);
        sendBytes();
    }

    template <typename T>
    void set(ClientEntry<T> &entry, T value)
    {
        entry.set(com_, value);
        sendBytes();
    }

    template <typename T>
    bool get(ClientEntry<T> &entry, T &value)
    {
        entry.get(com_);
        sendBytes();
        unsigned long start_time = millis();
        chThdSleepMilliseconds(2);
        while ((millis() < start_time + 10) && !getBytes(entry))
        {
            // this is the only change made in this implementation
            // This yields to another thread of a similar priority 
            // if there is one.
        }

        if (entry.IsFresh())
        {
            value = entry.get_reply();
            return true;
        }
        return false;
    }

    template <typename T>
    void save(ClientEntry<T> &entry)
    {
        entry.save(com_);
        sendBytes();
    }

private:
    GenericInterface com_;
    HardwareSerial *my_serial_;

    // This buffer is for passing around messages.
    uint8_t communication_buffer[64];
    // Stores length of message to send or receive
    uint8_t communication_length;

    void sendBytes()
    {
        // Grab outbound messages in the com queue, store into buffer
        // If it transferred something to communication_buffer...
        if (com_.GetTxBytes(communication_buffer, communication_length))
        {
            // Use Arduino serial hardware to send messages
            my_serial_->write(communication_buffer, communication_length);
        }
    }

    int8_t getBytes(ClientEntryAbstract &entry)
    {
        int8_t ret = 0;

        // Reads however many bytes are currently available
        communication_length = my_serial_->readBytes(communication_buffer, my_serial_->available());

        // Puts the recently read bytes into com’s receive queue
        com_.SetRxBytes(communication_buffer, communication_length);
        uint8_t *rx_data;  // temporary pointer to received type+data bytes
        uint8_t rx_length; // number of received type+data bytes
        // if we have a message packet to parse
        if (com_.PeekPacket(&rx_data, &rx_length))
        {
            ret = ParseMsg(rx_data, rx_length, entry);
            // Once we’re done with the message packet, drop it
            com_.DropPacket();
        }
        return ret;
    }
};