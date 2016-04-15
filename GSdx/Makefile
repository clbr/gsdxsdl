.PHONY: all clean

name = libGSdx-1.0.0.so

CXXFLAGS += -fno-operator-names -mfpmath=sse -fno-strict-aliasing -Wno-unknown-pragmas \
		-Wno-parentheses -Wunused-variable -std=gnu++11 -fvisibility=hidden \
		-I . -fPIC
CXXFLAGS += $(shell pkg-config --cflags gtk+-2.0)

LDFLAGS += -L /usr/X11R7/lib -lGL -lpng
LDFLAGS += $(shell pkg-config --libs gtk+-2.0)

all: $(name)

src = GLLoader.cpp \
	GLState.cpp \
	GPU.cpp \
	GPUDrawScanline.cpp \
	GPUDrawScanlineCodeGenerator.cpp \
	GPULocalMemory.cpp \
	GPURenderer.cpp \
	GPURendererSW.cpp \
	GPUSetupPrimCodeGenerator.cpp \
	GPUState.cpp \
	GS.cpp \
	GSAlignedClass.cpp \
	GSBlock.cpp \
	GSCapture.cpp \
	GSClut.cpp \
	GSCodeBuffer.cpp \
	GSCrc.cpp \
	GSDevice.cpp \
	GSDeviceOGL.cpp \
	GSDeviceSW.cpp \
	GSDeviceNull.cpp \
	GSDirtyRect.cpp \
	GSDrawingContext.cpp \
	GSDrawScanline.cpp \
	GSDrawScanlineCodeGenerator.cpp \
	GSDrawScanlineCodeGenerator.x86.avx.cpp \
	GSDrawScanlineCodeGenerator.x86.avx2.cpp \
	GSDrawScanlineCodeGenerator.x64.cpp \
	GSDrawScanlineCodeGenerator.x86.cpp \
	GSDrawScanlineCodeGenerator.x64.avx.cpp \
	GSDump.cpp \
	GSFunctionMap.cpp \
	GSLinuxDialog.cpp \
	GSLocalMemory.cpp \
	GSLzma.cpp \
	GSPerfMon.cpp \
	GSPng.cpp \
	GSRasterizer.cpp \
	GSRenderer.cpp \
	GSRendererCL.cpp \
	GSRendererHW.cpp \
	GSRendererNull.cpp \
	GSRendererOGL.cpp \
	GSRendererSW.cpp \
	GSSetting.cpp \
	GSSetupPrimCodeGenerator.cpp \
	GSSetupPrimCodeGenerator.x86.avx.cpp \
	GSSetupPrimCodeGenerator.x86.avx2.cpp \
	GSSetupPrimCodeGenerator.x64.avx.cpp \
	GSSetupPrimCodeGenerator.x86.cpp \
	GSSetupPrimCodeGenerator.x64.cpp \
	GSShaderOGL.cpp \
	GSState.cpp \
	GSTables.cpp \
	GSTexture.cpp \
	GSTextureCache.cpp \
	GSTextureCacheSW.cpp \
	GSTextureCacheOGL.cpp \
	GSTextureFXOGL.cpp \
	GSTextureOGL.cpp \
	GSTextureNull.cpp \
	GSTextureSW.cpp \
	GSThread.cpp \
	GSUtil.cpp \
	GSVector.cpp \
	GSVertexTrace.cpp \
	GSWnd.cpp \
	GSWndOGL.cpp \
	GSWndEGL.cpp \
	GSdx.cpp \
	stdafx.cpp

obj = $(src:.cpp=.o)

$(name): $(obj)
	$(CXX) -o $(name) -shared $(obj) $(CXXFLAGS) $(LDFLAGS)

clean:
	rm -f $(name) *.o
