/** @file
 *	@brief MAVLink comm protocol testsuite generated from custom_packets.xml
 *	@see http://qgroundcontrol.org/mavlink/
 */
#ifndef CUSTOM_PACKETS_TESTSUITE_H
#define CUSTOM_PACKETS_TESTSUITE_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef MAVLINK_TEST_ALL
#define MAVLINK_TEST_ALL
static void mavlink_test_common(uint8_t, uint8_t, mavlink_message_t *last_msg);
static void mavlink_test_custom_packets(uint8_t, uint8_t, mavlink_message_t *last_msg);

static void mavlink_test_all(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_test_common(system_id, component_id, last_msg);
	mavlink_test_custom_packets(system_id, component_id, last_msg);
}
#endif

#include "../common/testsuite.h"


static void mavlink_test_work_mode(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_work_mode_t packet_in = {
		5,72
    };
	mavlink_work_mode_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.idBPLA = packet_in.idBPLA;
        	packet1.mode = packet_in.mode;
        
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_work_mode_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_work_mode_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_work_mode_pack(system_id, component_id, &msg , packet1.idBPLA , packet1.mode );
	mavlink_msg_work_mode_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_work_mode_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.idBPLA , packet1.mode );
	mavlink_msg_work_mode_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_work_mode_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_work_mode_send(MAVLINK_COMM_1 , packet1.idBPLA , packet1.mode );
	mavlink_msg_work_mode_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_roll_value(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_roll_value_t packet_in = {
		5,72
    };
	mavlink_roll_value_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.idBPLA = packet_in.idBPLA;
        	packet1.mode = packet_in.mode;
        
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_roll_value_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_roll_value_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_roll_value_pack(system_id, component_id, &msg , packet1.idBPLA , packet1.mode );
	mavlink_msg_roll_value_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_roll_value_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.idBPLA , packet1.mode );
	mavlink_msg_roll_value_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_roll_value_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_roll_value_send(MAVLINK_COMM_1 , packet1.idBPLA , packet1.mode );
	mavlink_msg_roll_value_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_custom_packets(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_test_work_mode(system_id, component_id, last_msg);
	mavlink_test_roll_value(system_id, component_id, last_msg);
}

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // CUSTOM_PACKETS_TESTSUITE_H
