// MESSAGE WORK_MODE PACKING

#define MAVLINK_MSG_ID_WORK_MODE 150

typedef struct __mavlink_work_mode_t
{
 uint8_t idBPLA; /*< Plane ID*/
 uint8_t mode; /*< Work mode (0 for AP, 1 for RR)*/
} mavlink_work_mode_t;

#define MAVLINK_MSG_ID_WORK_MODE_LEN 2
#define MAVLINK_MSG_ID_150_LEN 2

#define MAVLINK_MSG_ID_WORK_MODE_CRC 226
#define MAVLINK_MSG_ID_150_CRC 226



#define MAVLINK_MESSAGE_INFO_WORK_MODE { \
	"WORK_MODE", \
	2, \
	{  { "idBPLA", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_work_mode_t, idBPLA) }, \
         { "mode", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_work_mode_t, mode) }, \
         } \
}


/**
 * @brief Pack a work_mode message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param idBPLA Plane ID
 * @param mode Work mode (0 for AP, 1 for RR)
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_work_mode_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint8_t idBPLA, uint8_t mode)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_WORK_MODE_LEN];
	_mav_put_uint8_t(buf, 0, idBPLA);
	_mav_put_uint8_t(buf, 1, mode);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_WORK_MODE_LEN);
#else
	mavlink_work_mode_t packet;
	packet.idBPLA = idBPLA;
	packet.mode = mode;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_WORK_MODE_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_WORK_MODE;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_WORK_MODE_LEN, MAVLINK_MSG_ID_WORK_MODE_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_WORK_MODE_LEN);
#endif
}

/**
 * @brief Pack a work_mode message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param idBPLA Plane ID
 * @param mode Work mode (0 for AP, 1 for RR)
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_work_mode_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint8_t idBPLA,uint8_t mode)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_WORK_MODE_LEN];
	_mav_put_uint8_t(buf, 0, idBPLA);
	_mav_put_uint8_t(buf, 1, mode);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_WORK_MODE_LEN);
#else
	mavlink_work_mode_t packet;
	packet.idBPLA = idBPLA;
	packet.mode = mode;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_WORK_MODE_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_WORK_MODE;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_WORK_MODE_LEN, MAVLINK_MSG_ID_WORK_MODE_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_WORK_MODE_LEN);
#endif
}

/**
 * @brief Encode a work_mode struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param work_mode C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_work_mode_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_work_mode_t* work_mode)
{
	return mavlink_msg_work_mode_pack(system_id, component_id, msg, work_mode->idBPLA, work_mode->mode);
}

/**
 * @brief Encode a work_mode struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param work_mode C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_work_mode_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_work_mode_t* work_mode)
{
	return mavlink_msg_work_mode_pack_chan(system_id, component_id, chan, msg, work_mode->idBPLA, work_mode->mode);
}

/**
 * @brief Send a work_mode message
 * @param chan MAVLink channel to send the message
 *
 * @param idBPLA Plane ID
 * @param mode Work mode (0 for AP, 1 for RR)
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_work_mode_send(mavlink_channel_t chan, uint8_t idBPLA, uint8_t mode)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_WORK_MODE_LEN];
	_mav_put_uint8_t(buf, 0, idBPLA);
	_mav_put_uint8_t(buf, 1, mode);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_WORK_MODE, buf, MAVLINK_MSG_ID_WORK_MODE_LEN, MAVLINK_MSG_ID_WORK_MODE_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_WORK_MODE, buf, MAVLINK_MSG_ID_WORK_MODE_LEN);
#endif
#else
	mavlink_work_mode_t packet;
	packet.idBPLA = idBPLA;
	packet.mode = mode;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_WORK_MODE, (const char *)&packet, MAVLINK_MSG_ID_WORK_MODE_LEN, MAVLINK_MSG_ID_WORK_MODE_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_WORK_MODE, (const char *)&packet, MAVLINK_MSG_ID_WORK_MODE_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_WORK_MODE_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_work_mode_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t idBPLA, uint8_t mode)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;
	_mav_put_uint8_t(buf, 0, idBPLA);
	_mav_put_uint8_t(buf, 1, mode);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_WORK_MODE, buf, MAVLINK_MSG_ID_WORK_MODE_LEN, MAVLINK_MSG_ID_WORK_MODE_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_WORK_MODE, buf, MAVLINK_MSG_ID_WORK_MODE_LEN);
#endif
#else
	mavlink_work_mode_t *packet = (mavlink_work_mode_t *)msgbuf;
	packet->idBPLA = idBPLA;
	packet->mode = mode;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_WORK_MODE, (const char *)packet, MAVLINK_MSG_ID_WORK_MODE_LEN, MAVLINK_MSG_ID_WORK_MODE_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_WORK_MODE, (const char *)packet, MAVLINK_MSG_ID_WORK_MODE_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE WORK_MODE UNPACKING


/**
 * @brief Get field idBPLA from work_mode message
 *
 * @return Plane ID
 */
static inline uint8_t mavlink_msg_work_mode_get_idBPLA(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  0);
}

/**
 * @brief Get field mode from work_mode message
 *
 * @return Work mode (0 for AP, 1 for RR)
 */
static inline uint8_t mavlink_msg_work_mode_get_mode(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  1);
}

/**
 * @brief Decode a work_mode message into a struct
 *
 * @param msg The message to decode
 * @param work_mode C-struct to decode the message contents into
 */
static inline void mavlink_msg_work_mode_decode(const mavlink_message_t* msg, mavlink_work_mode_t* work_mode)
{
#if MAVLINK_NEED_BYTE_SWAP
	work_mode->idBPLA = mavlink_msg_work_mode_get_idBPLA(msg);
	work_mode->mode = mavlink_msg_work_mode_get_mode(msg);
#else
	memcpy(work_mode, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_WORK_MODE_LEN);
#endif
}
