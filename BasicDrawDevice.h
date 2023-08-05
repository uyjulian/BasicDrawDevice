
#ifndef BASIC_DRAW_DEVICE_H
#define BASIC_DRAW_DEVICE_H

#if 0
#include "DrawDevice.h"
#endif
#if 1
#include "tTVPDrawDevice.h"
#include "DrawDeviceTmpl.h"
#endif
#include <d3d9.h>

// 吉里吉里2上での動作が不要であれば0にする
#ifndef USE_K2DD
#define USE_K2DD 1
#endif

//---------------------------------------------------------------------------
//! @brief		「Basic」デバイス(もっとも基本的な描画を行うのみのデバイス)
//---------------------------------------------------------------------------
class tTVPBasicDrawDevice : public tTVPDrawDevice
{
	typedef tTVPDrawDevice inherited;
	typedef tTVPBasicDrawDevice selfclass;

	HWND TargetWindow;
	bool IsMainWindow;
	bool DrawUpdateRectangle;
	bool BackBufferDirty;

	IDirect3D9*				Direct3D;
	IDirect3DDevice9*		Direct3DDevice;
	IDirect3DTexture9*		Texture;
	D3DPRESENT_PARAMETERS	D3dPP;
	D3DDISPLAYMODE			DispMode;

	UINT	CurrentMonitor;
	void*	TextureBuffer; //!< テクスチャのサーフェースへのメモリポインタ
	long	TexturePitch; //!< テクスチャのピッチ

	tjs_uint TextureWidth; //!< テクスチャの横幅
	tjs_uint TextureHeight; //!< テクスチャの縦幅

	bool ShouldShow; //!< show で実際に画面に画像を転送すべきか

	tjs_uint VsyncInterval;

public:
	tTVPBasicDrawDevice(); //!< コンストラクタ
protected:
	~tTVPBasicDrawDevice(); //!< デストラクタ

private:
	void InvalidateAll();

	UINT GetMonitorNumber( HWND window );

	bool IsTargetWindowActive() const;

	bool GetDirect3D9Device();
	HRESULT InitializeDirect3DState();
	HRESULT DecideD3DPresentParameters();

	bool CreateD3DDevice();
	void DestroyD3DDevice();

	bool CreateTexture();
	void DestroyTexture();

	void TryRecreateWhenDeviceLost();
	void ErrorToLog( HRESULT hr );
	void CheckMonitorMoved();

private:
	virtual void OnManagerSetError(tjs_error r);

public:
	void SetToRecreateDrawer() { DestroyD3DDevice(); }

public:
	void EnsureDevice();

//---- LayerManager の管理関連
	virtual void TJS_INTF_METHOD AddLayerManager(iTVPLayerManager * manager);

//---- 描画位置・サイズ関連
	virtual void TJS_INTF_METHOD SetTargetWindow(HWND wnd, bool is_main);
	virtual void TJS_INTF_METHOD SetDestRectangle(const tTVPRect & rect);
	virtual void TJS_INTF_METHOD NotifyLayerResize(iTVPLayerManager * manager);

//---- 再描画関連
	virtual void TJS_INTF_METHOD Show();
	virtual bool TJS_INTF_METHOD WaitForVBlank( tjs_int* in_vblank, tjs_int* delayed );

//---- LayerManager からの画像受け渡し関連
	virtual void TJS_INTF_METHOD StartBitmapCompletion(iTVPLayerManager * manager);
	virtual void TJS_INTF_METHOD NotifyBitmapCompleted(iTVPLayerManager * manager,
		tjs_int x, tjs_int y, const void * bits, const BITMAPINFO * bitmapinfo,
		const tTVPRect &cliprect, tTVPLayerType type, tjs_int opacity);
	virtual void TJS_INTF_METHOD EndBitmapCompletion(iTVPLayerManager * manager);

//---- デバッグ支援
	virtual void TJS_INTF_METHOD SetShowUpdateRect(bool b);

//---- フルスクリーン
	virtual bool TJS_INTF_METHOD SwitchToFullScreen( HWND window, tjs_uint w, tjs_uint h, tjs_uint bpp, tjs_uint color, bool changeresolution );
	virtual void TJS_INTF_METHOD RevertFromFullScreen( HWND window, tjs_uint w, tjs_uint h, tjs_uint bpp, tjs_uint color );

};
//---------------------------------------------------------------------------

class tTVPBasicDrawDeviceWrapper : public DrawDeviceIntfTmpl<tTVPBasicDrawDevice> {};

//---------------------------------------------------------------------------
// tTJSNI_BasicDrawDevice
//---------------------------------------------------------------------------
class tTJSNI_BasicDrawDevice :
	public tTJSNativeInstance
{
	typedef tTJSNativeInstance inherited;

	tTVPBasicDrawDevice * Device;

public:
	tTJSNI_BasicDrawDevice();
	~tTJSNI_BasicDrawDevice();
	tjs_error TJS_INTF_METHOD
		Construct(tjs_int numparams, tTJSVariant **param,
			iTJSDispatch2 *tjs_obj);
	void TJS_INTF_METHOD Invalidate();

public:
	tTVPBasicDrawDevice * GetDevice() const { return Device; }

};
//---------------------------------------------------------------------------



#if 0
//---------------------------------------------------------------------------
// tTJSNC_BasicDrawDevice
//---------------------------------------------------------------------------
class tTJSNC_BasicDrawDevice : public tTJSNativeClass
{
public:
	tTJSNC_BasicDrawDevice();

	static tjs_uint32 ClassID;

private:
	iTJSNativeInstance *CreateNativeInstance();
};
//---------------------------------------------------------------------------
#else
class tTJSNC_BasicDrawDevice
{
public:
	static tTJSNativeClassForPlugin *CreateNativeClass();
	static tjs_uint32 ClassID;
	static iTJSNativeInstance *CreateNativeInstance();
};
#endif


#endif // BASIC_DRAW_DEVICE_H