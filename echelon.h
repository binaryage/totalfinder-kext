//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TotalFinder.kext from BinaryAge (Echelon)
//   a kernel-level file renaming watcher for TotalFinder
//   more: http://blog.binaryage.com/totalfinder-alpha
//

// following line will be patched by the build script
#define ECHELON_RELEASE_VERSION "debug"

#define ECHELON_BUNDLE_ID "com.binaryage.totalfinder.kext" // also modify Info.plist!
#define ECHELON_PATH_MAX 1024 // this should match OS PATH_MAX constant
#define ECHELON_DSCACHE_PREFIX "/usr/local/.dscache"
#define ECHELON_VERSION 1

#define ECHELON_OP_RENAME 0
#define ECHELON_OP_DELETE 1

// using binary struct passing between kernel and user-space
// do you believe that your compiler does not screw this structure?
// http://en.wikipedia.org/wiki/Data_structure_alignment
#pragma pack(push)
#pragma pack(1)

struct EchelonMessage {
    unsigned char version; // current version == ECHELON_VERSION
    unsigned char operation;
    char  path1[ECHELON_PATH_MAX];
    char  path2[ECHELON_PATH_MAX];
};

#pragma pack(pop)