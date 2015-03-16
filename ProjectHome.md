This simple program generates thumbnails of digital camera raw image files using libopenraw and GDK.  It supports the same file formats as libopenraw (http://libopenraw.freedesktop.org/wiki/FileFormats).

This thumbnailer is designed to be small, lightweight and fast.  It is primarily intended to be used with file managers (although it could easily be used by a photograph management program) and is used by [thunar-thumbnailers](http://goodies.xfce.org/projects/thunar-plugins/thunar-thumbnailers).

Usage:
raw-thumbnailer -i input\_file -o output\_file -s size

See also, [ffmpegthumbnailer](http://code.google.com/p/ffmpegthumbnailer): an excellent thumbnailer for video files.