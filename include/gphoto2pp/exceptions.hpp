/** \file
 * \author Copyright (c) 2013 maldworth <https://github.com/maldworth>
 *
 * \note
 * This file is part of gphoto2pp
 *
 * \note
 * gphoto2pp is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * \note
 * gphoto2pp is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * \note
 * You should have received a copy of the GNU Lesser General Public
 * License along with gphoto2pp.
 * If not, see http://www.gnu.org/licenses
 */

#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <stdexcept>

namespace gphoto2pp {

/**
 * @brief libgphoto2 return codes encapsulated in C++ enum class.
 *
 * For more information about these return codes lookup in libgphoto2 documentation.
 */
enum class GPhoto2ResultCodesWrapper {
    Ok = 0, // Everything is okay

    //*** IOLib Errors ***
    Error = -1,              // Generic Error
    BadParameters = -2,      // Bad paramters passed
    NoMemory = -3,           // Out of memory
    Library = -4,            // Error in the camera driver
    UnknownPort = -5,        // Unknown libgphoto2 port passed
    NotSupported = -6,       // Functionality not supported
    Io = -7,                 // Generic I/O error
    FixedLimitExceeded = -8, // Buffer overflow of internal structure
    TimeOut = -10,           // Operation timed out
    IoSupportedSerial = -20, // Serial ports not supported
    IoSupportedUsb = -21,    // USB ports not supported
    IoInit = -31,            // Error initialising I/O
    IoRead = -34,            // I/O during read
    IoWrite = -35,           // I/O during write
    IoUpdate = -37,          // I/O during update of settings
    IoSerialSpeed = -41,     // Specified serial speed not possible.
    IoUsbClearHalt = -51,    // Error during USB Clear HALT
    IoUsbFind = -52,         // Error when trying to find USB device
    IoUsbClaim = -53,        // Error when trying to claim the USB device
    IoLock = -60,            // Error when trying to lock the device
    Hal = -70,               // Unspecified error when talking to HAL

    //*** Camlib Errors ***
    CorruptedData = -102,     // Corrupted data received
    FileExists = -103,        // File already exists
    ModelNotFound = -105,     // Specified camera model was not found
    DirectoryNotFound = -107, // Specified directory was not found
    FileNotFound = -108,      // Specified file was not found
    DirectoryExists = -109,   // Specified directory already exists
    CameraBusy = -110,        // The camera is already busy
    PathNotAbsolut = -111,    // Path is not absolute
    Cancel = -112,            // Cancellation successful.
    CameraError = -113,       // Unspecified camera error
    OsFailure = -114,         // Unspecified failure of the operating system
    NoSpace = -115,           // Not enough space
};

namespace exceptions {

/**
 * \class GPhoto2ppException
 * Base class for all exceptions in this library
 */
class GPhoto2ppException : public std::runtime_error {
public:
    GPhoto2ppException(std::string &&message) : std::runtime_error(message) {}
};

/**
 * \class gphoto2_exception
 * Represents any error received from a gphoto2 method call with a value < 0
 */
class gphoto2_exception : public GPhoto2ppException {
public:
    gphoto2_exception(int result, std::string &&gp_result_string)
        : GPhoto2ppException(std::move(gp_result_string)),
          m_resultCode(static_cast<GPhoto2ResultCodesWrapper>(result)) {}

    /**
     * \brief The error code received from the gphoto2 method
     */
    GPhoto2ResultCodesWrapper getResultCode() const { return m_resultCode; }

private:
    const GPhoto2ResultCodesWrapper m_resultCode;
};

class InvalidLinkedVersionException : public GPhoto2ppException {
public:
    InvalidLinkedVersionException(std::string &&message) : GPhoto2ppException(std::move(message)) {}
};

class CameraWrapperException : public GPhoto2ppException {
public:
    CameraWrapperException(std::string &&message) : GPhoto2ppException(std::move(message)) {}
};

class HelperException : public GPhoto2ppException {
public:
    HelperException(std::string &&message) : GPhoto2ppException(std::move(message)) {}
};

class NoCameraFoundError : public GPhoto2ppException {
public:
    NoCameraFoundError(std::string &&message) : GPhoto2ppException(std::move(message)) {}
};

class ArgumentException : public GPhoto2ppException {
public:
    ArgumentException(std::string &&message) : GPhoto2ppException(std::move(message)) {}
};

// Widget Exceptions
class InvalidWidgetType : public GPhoto2ppException {
public:
    InvalidWidgetType(std::string &&message) : GPhoto2ppException(std::move(message)) {}
};

class NullWidget : public GPhoto2ppException {
public:
    NullWidget(std::string &&message) : GPhoto2ppException(std::move(message)) {}
};

class IndexOutOfRange : public GPhoto2ppException {
public:
    IndexOutOfRange(std::string &&message) : GPhoto2ppException(std::move(message)) {}
};

class ValueOutOfLimits : public GPhoto2ppException {
public:
    ValueOutOfLimits(std::string &&message) : GPhoto2ppException(std::move(message)) {}
};

} // namespace exceptions
} // namespace gphoto2pp

#endif // EXCEPTIONS_HPP
