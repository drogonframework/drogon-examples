#ifndef LIBBACKEND_HEADER_CONST_HH
#define LIBBACKEND_HEADER_CONST_HH
#include <string>

namespace libbackend {
namespace HTTP_HEADER_ALIASES {

inline static const std::string HOST = "Host";
inline static const std::string ORIGIN = "Origin";
inline static const std::string REFERER = "Referer";
inline static const std::string ACCEPT_LANGUAGE = "Accept-Language";
inline static const std::string ACCESS_CONTROL_ALLOW_ORIGIN = "Access-Control-Allow-Origin";
inline static const std::string ACCESS_CONTROL_ALLOW_CREDENTIALS = "Access-Control-Allow-Credentials";
inline static const std::string STRICT_TRANSPORT_SECURITY = "Strict-Transport-Security";
inline static const std::string CROSS_ORIGIN_OPENER_POLICY = "Cross-Origin-Opener-Policy";
inline static const std::string CROSS_ORIGIN_EMBEDDER_POLICY = "Cross-Origin-Embedder-Policy";
inline static const std::string USER_AGENT = "User-Agent";
inline static const std::string X_FRAME_OPTIONS = "X-Frame-Options";
inline static const std::string X_REAL_IP = "X-Real-Ip";

} // namespace HTTP_HEADER_ALIASES
} // namespace libbackend

#endif // LIBBACKEND_HEADER_CONST_HH