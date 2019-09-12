// MESSAGE ROLL_VALUE PACKING

#define MAVLINK_MSG_ID_ROLL_VALUE 151

typedef struct __mavlink_roll_value_t
{
 uint8_t idBPLA; /*< Plane ID*/
 uint8_t mode; /*< Roll value*/
} mavlink_roll_value_t;

#define MAVLINK_MSG_ID_ROLL_VALUE_LEN 2
#define MAVLINK_MSG_ID_151_LEN 2

#define MAVLINK_MSG_ID_ROLL_VALUE_CRC 107
#define MAVLINK_MSG_ID_151_CRC 107



#define MAVLINK_MESSAGE_INFO_ROLL_VALUE { \
	"ROLL_VALUE", \
	2, \
	{  { "idBPLA", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_roll_value_t, idBPLA) }, \
         { "mode", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_roll_value_t, mode) }, \
         } \
}


/**
 * @brief Pack a roll_value message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param idBPLA Plane ID
 * @param mode Roll value
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_roll_value_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint8_t idBPLA, uint8_t mode)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_ROLL_VALUE_LEN];
	_mav_put_uint8_t(buf, 0, idBPLA);
	_mav_put_uint8_t(buf, 1, mode);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ROLL_VALUE_LEN);
#else
	mavlink_roll_value_t packet;
	packet.idBPLA = idBPLA;
	packet.mode = mode;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ROLL_VALUE_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_ROLL_VALUE;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_ROLL_VALUE_LEN, MAVLINK_MSG_ID_ROLL_VALUE_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_ROLL_VALUE_LEN);
#endif
}

/**
 * @brief Pack a roll_value message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param idBPLA Plane ID
 * @param mode Roll value
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_roll_value_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint8_t idBPLA,uint8_t mode)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_ROLL_VALUE_LEN];
	_mav_put_uint8_t(buf, 0, idBPLA);
	_mav_put_uint8_t(buf, 1, mode);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ROLL_VALUE_LEN);
#else
	mavlink_roll_value_t packet;
	packet.idBPLA = idBPLA;
	packet.mode = mode;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ROLL_VALUE_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_ROLL_VALUE;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_ROLL_VALUE_LEN, MAVLINK_MSG_ID_ROLL_VALUE_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_ROLL_VALUE_LEN);
#endif
}

/**
 * @brief Encode a roll_value struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param roll_value C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_roll_value_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_roll_value_t* roll_value)
{
	return mavlink_msg_roll_value_pack(system_id, component_id, msg, roll_value->idBPLA, roll_value->mode);
}

/**
 * @brief Encode a roll_value struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param roll_value C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_roll_value_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_roll_value_t* roll_value)
{
	return mavlink_msg_roll_value_pack_chan(system_id, component_id, chan, msg, roll_value->idBPLA, roll_value->mode);
}

/**
 * @brief Send a roll_value message
 * @param chan MAVLink channel to send the message
 *
 * @param idBPLA Plane ID
 * @param mode Roll value
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_roll_value_send(mavlink_channel_t chan, uint8_t idBPLA, uint8_t mode)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_ROLL_VALUE_LEN];
	_mav_put_uint8_t(buf, 0, idBPLA);
	_mav_put_uint8_t(buf, 1, mode);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ROLL_VALUE, buf, MAVLINK_MSG_ID_ROLL_VALUE_LEN, MAVLINK_MSG_ID_ROLL_VALUE_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ROLL_VALUE, buf, MAVLINK_MSG_ID_ROLL_VALUE_LEN);
#endif
#else
	mavlink_roll_value_t packet;
	packet.idBPLA = idBPLA;
	packet.mode = mode;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ROLL_VALUE, (const char *)&packet, MAVLINK_MSG_ID_ROLL_VALUE_LEN, MAVLINK_MSG_ID_ROLL_VALUE_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ROLL_VALUE, (const char *)&packet, MAVLINK_MSG_ID_ROLL_VALUE_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_ROLL_VALUE_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_roll_value_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t idBPLA, uint8_t mode)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;
	_mav_put_uint8_t(buf, 0, idBPLA);
	_mav_put_uint8_t(buf, 1, mode);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ROLL_VALUE, buf, MAVLINK_MSG_ID_ROLL_VALUE_LEN, MAVLINK_MSG_ID_ROLL_VALUE_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ROLL_VALUE, buf, MAVLINK_MSG_ID_ROLL_VALUE_LEN);
#endif
#else
	mavlink_roll_value_t *packet = (mavlink_roll_value_t *)msgbuf;
	packet->idBPLA = idBPLA;
	packet->mode = mode;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ROLL_VALUE, (const char *)packet, MAVLINK_MSG_ID_ROLL_VALUE_LEN, MAVLINK_MSG_ID_ROLL_VALUE_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ROLL_VALUE, (const char *)packet, MAVLINK_MSG_ID_ROLL_VALUE_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE ROLL_VALUE UNPACKING


/**
 * @brief Get field idBPLA from roll_value message
 *
 * @return Plane ID
 */
static inline uint8_t mavlink_msg_roll_value_get_idBPLA(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  0);
}

/**
 * @brief Get field mode from roll_value message
 *
 * @return Roll value
 */
static inline uint8_t mavlink_msg_roll_value_get_mode(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  1);
}

/**
 * @brief Decode a roll_value message into a struct
 *
 * @param msg The message to decode
 * @param roll_value C-struct to decode the message contents into
 */
static inline void mavlink_msg_roll_value_decode(const mavlink_message_t* msg, mavlink_roll_value_t* roll_value)
{
#if MAVLINK_NEED_BYTE_SWAP
	roll_value->idBPLA = mavlink_msg_roll_value_get_idBPLA(msg);
	roll_value->mode = mavlink_msg_roll_value_get_mode(msg);
#else
	memcpy(roll_value, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_ROLL_VALUE_LEN);
#endif
}
