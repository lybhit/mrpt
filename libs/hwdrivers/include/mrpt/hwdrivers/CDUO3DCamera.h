/* +---------------------------------------------------------------------------+
   |                 The Mobile Robot Programming Toolkit (MRPT)               |
   |                                                                           |
   |                          http://www.mrpt.org/                             |
   |                                                                           |
   | Copyright (c) 2005-2013, Individual contributors, see AUTHORS file        |
   | Copyright (c) 2005-2013, MAPIR group, University of Malaga                |
   | Copyright (c) 2012-2013, University of Almeria                            |
   | All rights reserved.                                                      |
   |                                                                           |
   | Redistribution and use in source and binary forms, with or without        |
   | modification, are permitted provided that the following conditions are    |
   | met:                                                                      |
   |    * Redistributions of source code must retain the above copyright       |
   |      notice, this list of conditions and the following disclaimer.        |
   |    * Redistributions in binary form must reproduce the above copyright    |
   |      notice, this list of conditions and the following disclaimer in the  |
   |      documentation and/or other materials provided with the distribution. |
   |    * Neither the name of the copyright holders nor the                    |
   |      names of its contributors may be used to endorse or promote products |
   |      derived from this software without specific prior written permission.|
   |                                                                           |
   | THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS       |
   | 'AS IS' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED |
   | TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR|
   | PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE |
   | FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL|
   | DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR|
   |  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)       |
   | HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,       |
   | STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN  |
   | ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE           |
   | POSSIBILITY OF SUCH DAMAGE.                                               |
   +---------------------------------------------------------------------------+ */
#ifndef CDUO3DCamera_H
#define CDUO3DCamera_H

#include <mrpt/slam/CObservationStereoImages.h>
#include <mrpt/slam/CObservationIMU.h>
#include <mrpt/vision/CStereoRectifyMap.h>

#include <mrpt/hwdrivers/link_pragmas.h>
#include <mrpt/utils/CUncopiable.h>

#include <mrpt/otherlibs/do_opencv_includes.h> 

// duo3d header files
#if MRPT_HAS_DUO3D
#		include <DUOLib.h>
#		pragma comment(lib, "DUOLib.lib")
#endif

namespace mrpt
{
	namespace hwdrivers
	{
		/** Options used when creating a camera capture object of type CImageGrabber_FlyCapture2   \ingroup mrpt_hwdrivers_grp */
		struct HWDRIVERS_IMPEXP TCaptureOptions_DUO3D
		{
			enum TYMLReadResult {yrr_NAME_NON_CONSISTENT,yrr_EMPTY,yrr_OK};

			TCaptureOptions_DUO3D();

			/** @name Image settings
			  * @{ */
			int			m_img_width;			//!< (Default = 640) Width of the captured image.
			int			m_img_height;			//!< (Default = 480) Height of the captured image.
			float		m_fps;					//!< (Default = 30) Frames per second <= 30.
			float		m_exposure;				//!< (Default = 50) Exposure value.
			float		m_led;					//!< (Default = 25) Led intensity (some device models).
			float		m_gain;					//!< (Default = 10) Camera gain.
			/** @} */

			/** @name Behaviour selection
			  * @{ */
			bool		m_capture_imu;			//!< (Default = false) Capture IMU data.
			bool		m_capture_rectified;	//!< (Default = true) Rectify images. Rectification map must be provided \sa m_rectify_map_filename.
			bool		m_calibration_from_file;//!< (Default = true) Get calibration information from files provided by DUO3D Calibration App.
			/** @} */
			
			/** @name Files specification
			  * @{ */
			std::string	m_rectify_map_filename;	//!< Rectification map file provided by DUO3D Calibration App (YML format).
			std::string	m_intrinsic_filename;	//!< Intrinsic parameters file provided by DUO3D Calibration App (YML format).
			std::string	m_extrinsic_filename;	//!< Extrinsic parameters file provided by DUO3D Calibration App (YML format).
			/** @} */

			/** @name Others
			  * @{ */
			mrpt::utils::TStereoCamera	m_stereo_camera;
			cv::Mat		m_rectify_map_left_x;
			cv::Mat		m_rectify_map_left_y;
			cv::Mat		m_rectify_map_right_x;
			cv::Mat		m_rectify_map_right_y;
			/** @} */

			/** Loads all the options from a config file.
			  * Expected format:
			  *
			  * \code
			  * [sectionName]
			  *		image_width   			= 640			// [int]	x Resolution
			  *		image_height  			= 480			// [int]	y Resolution
			  *		fps						= 30			// [int]	Frames per second (<= 30)
			  *		exposure				= 50			// [int]	Exposure value (1..100)
			  *		led						= 0				// [int]	Led intensity (only for some device models) (1..100).
			  *		gain					= 50			// [int]	Camera gain (1..100)
			  *		capture_rectified 		= false			// [bool]	Rectify captured images
			  *		capture_imu 			= true			// [bool]	Capture IMU data from DUO3D device (if available)
			  *		calibration_from_file	= true			// [bool]	Use YML calibration files provided by calibration application supplied with DUO3D device
			  *	  	intrinsic_filename		= ""			// [string]	Intrinsic parameters file. This filename should contain a substring _RWWWxHHH_ with WWW being the image width and HHH the image height, as provided by the calibration application.
			  *		extrinsic_filename		= ""			// [string]	Extrinsic parameters file. This filename should contain a substring _RWWWxHHH_ with WWW being the image width and HHH the image height, as provided by the calibration application.
			  *		rectify_map_filename	= ""			// [string]	Rectification map file. This filename should contain a substring _RWWWxHHH_ with WWW being the image width and HHH the image height, as provided by the calibration application.
			  *
			  * \endcode
			  * \note All parameter names may have an optional prefix, set with the "prefix" parameter.
			  *  For example, if prefix="LEFT_", the expected variable name "camera_index" in the config section will be "LEFT_camera_index", and so on.
			  */
			void  loadOptionsFrom(
				const mrpt::utils::CConfigFileBase & configSource,
				const std::string & sectionName,
				const std::string & prefix = std::string() );

			TYMLReadResult m_camera_int_params_from_yml( const std::string & _file_name = std::string() );
			TYMLReadResult m_camera_ext_params_from_yml( const std::string & _file_name = std::string() );
			TYMLReadResult m_rectify_map_from_yml( const std::string & _file_name = std::string() );

		}; // end-TCaptureOptions_DUO3D

		/** This "software driver" implements the communication protocol for interfacing a DUO3D Stereo Camera 
		  *
		  *   For an example of usage see the example in "samples/DUO3D_camera_test".
		  *   See also the example configuration file for rawlog-grabber in "share/mrpt/config_files/rawlog-grabber".
		  *
		  *  \code
		  *  PARAMETERS IN THE ".INI"-LIKE CONFIGURATION STRINGS:
		  * -------------------------------------------------------
		  *   [supplied_section_name]
		  *		image_width   			= 640			// [int]	x Resolution
		  *		image_height  			= 480			// [int]	y Resolution
		  *		fps						= 30			// [int]	Frames per second (<= 30)
		  *		exposure				= 50			// [int]	Exposure value (1..100)
		  *		led						= 0				// [int]	Led intensity (only for some device models) (1..100).
		  *		gain					= 50			// [int]	Camera gain (1..100)
		  *		capture_rectified 		= false			// [bool]	Rectify captured images
		  *		capture_imu 			= true			// [bool]	Capture IMU data from DUO3D device (if available)
		  *		calibration_from_file	= true			// [bool]	Use YML calibration files provided by calibration application supplied with DUO3D device
		  *	  	intrinsic_filename		= ""			// [string]	Intrinsic parameters file. This filename should contain a substring _RWWWxHHH_ with WWW being the image width and HHH the image height, as provided by the calibration application.
		  *		extrinsic_filename		= ""			// [string]	Extrinsic parameters file. This filename should contain a substring _RWWWxHHH_ with WWW being the image width and HHH the image height, as provided by the calibration application.
		  *		rectify_map_filename	= ""			// [string]	Rectification map file. This filename should contain a substring _RWWWxHHH_ with WWW being the image width and HHH the image height, as provided by the calibration application.
		  *
		  *   pose_x=0.21	// camera 3D position in the robot (meters)
		  *   pose_y=0
		  *   pose_z=0.34
		  *   pose_yaw=0	// Angles in degrees
		  *   pose_pitch=0
		  *   pose_roll=0
		  *  \endcode
		  *
		  * \ingroup mrpt_hwdrivers_grp
		  */
		class HWDRIVERS_IMPEXP CDUO3DCamera : public mrpt::utils::CUncopiable
		{

		protected:
			// members
			// [USER-DEFINED]
			TCaptureOptions_DUO3D	m_options;
			
			// [INTERNAL]
			mrpt::vision::CStereoRectifyMap m_rectify_map;

#if MRPT_HAS_DUO3D
			DUOInstance				m_duo;
			PDUOFrame				m_pframe_data;
			HANDLE					m_evFrame;
#endif

		public:
			/** Default Constructor (does not open the camera) */
			CDUO3DCamera();

			/** Constructor: tries to open the camera with the given options. Raises an exception on error. \sa open() */
			CDUO3DCamera( const TCaptureOptions_DUO3D & options );

			/** Destructor  */
			virtual ~CDUO3DCamera();

			/** Returns the current settings of the camera */
			const TCaptureOptions_DUO3D & getCameraOptions() const { return m_options; }

			/** Tries to open the camera with the given options, and starts capturing. Raises an exception on error.
			  * \param[in] startCapture If set to false, the camera is only opened and configured, but a posterior call to startCapture() is required to start grabbing data.
			  * \sa close(), startCapture()
			  */
			void open( const TCaptureOptions_DUO3D & options, const bool startCapture = true );

			/** Start the actual data capture of the camera. Must be called after open(), only when "startCapture" was set to false.
			  */
			void startCapture();

			/** Stop capture. */
			void stopCapture();

			/** Stop capture and closes the opened camera, if any. Called automatically on object destruction. */
			void close();

			/** Specific laser scanner "software drivers" must process here new data from the I/O stream, and, if a whole scan has arrived, return it.
			  *  This method will be typically called in a different thread than other methods, and will be called in a timely fashion.
			  */
			void getObservations(
				mrpt::slam::CObservationStereoImages	& outObservation_img,
				mrpt::slam::CObservationIMU				& outObservation_imu,
				bool									& there_is_img,
				bool									& there_is_imu );

			/** Indicates if the camera is grabbing IMU data */
			inline bool captureIMUIsSet() { return m_options.m_capture_imu; }

#if MRPT_HAS_DUO3D
			inline HANDLE getEvent() { return this->m_evFrame; }
			inline void setDataFrame( const PDUOFrame & frame ) { this->m_pframe_data = frame; }
#endif
		protected:
#if MRPT_HAS_DUO3D
			/** Queries the DUO3D Camera firmware version */
			bool inline queryVersion(std::string version, bool printOutVersion = false)
			{
				version = std::string(GetLibVersion());
				if( printOutVersion ) std::cout << "DUO3D Camera library version: " << version << std::endl;
				return true;
			}
			void CALLBACK m_duo_callback(const PDUOFrame pFrameData, void *pUserData);
			
			/** Gets a stereo frame from the DUO3D Camera */
			PDUOFrame m_get_duo_frame();
#endif
			/** Opens DUO3D camera */
			bool m_open_duo_camera(int width, int height, float fps);
			
			/** Closes DUO3D camera */
			void m_close_duo_camera();
			
			/** Sets DUO3D camera Exposure setting */
			void m_set_exposure(float value);
			
			/** Sets DUO3D camera Gain setting  */
			void m_set_gain(float value);
			
			/** Sets DUO3D camera LED setting  */
			void m_set_led(float value);
		};	// End of class
	} // End of namespace
}; // End of namespace
#endif
