/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package com.wanbaox.dots;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.widget.FrameLayout;

import com.google.ads.AdRequest;
import com.google.ads.AdSize;
import com.google.ads.AdView;

public class dots extends Cocos2dxActivity{

	private static Cocos2dxActivity instance;
	
	public final static int S_HANDLER_SHOW_BANNER = 1;
	public final static int S_HANDLER_DELETE_BANNER = 2;
	public final static int S_HANDLER_RATE = 3;
	public final static int S_HANDLER_GOTOQQ = 4;
	public static AdView adView;
	public static Handler sHandler = new Handler(new Handler.Callback() {
		
		@Override
		public boolean handleMessage(Message msg) {
			
			switch (msg.what) {
			case S_HANDLER_SHOW_BANNER:

		    	if (dots.adView!=null) {


		    		dots.adView.setVisibility(View.VISIBLE);

				}else{
					
					// 创建 adView
				    adView = new AdView(instance, AdSize.SMART_BANNER, "a152b7ebd9673fe");

				    adView.setGravity(Gravity.BOTTOM);
				    
				    ViewGroup v=(ViewGroup)instance.getWindow().getDecorView().findViewById(android.R.id.content);
				    

					FrameLayout parent = (FrameLayout)v.getChildAt(0);

				    // 在其中添加 adView
					parent.addView(adView);

				    // 启动一般性请求并在其中加载广告
				    adView.loadAd(new AdRequest());
				}
				break;
			case S_HANDLER_DELETE_BANNER:

		    	if (dots.adView!=null) {


		    		dots.adView.setVisibility(View.INVISIBLE);

				}
				break;
			case S_HANDLER_RATE:
			{
				

				String mAddress = "market://details?id=" + instance.getPackageName(); 
				Intent marketIntent = new Intent("android.intent.action.VIEW");  
				marketIntent .setData(Uri.parse(mAddress ));  
				instance.startActivity(marketIntent );
				break;
			}

			case S_HANDLER_GOTOQQ:
			{

				String mAddress = "http://user.qzone.qq.com/360348837/"; 
				Intent marketIntent = new Intent("android.intent.action.VIEW");  
				marketIntent .setData(Uri.parse(mAddress ));  
				instance.startActivity(marketIntent );
				break;
				
			}
			default:
				break;
			}
			return false;
		}
	});
	
    protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);			
		
		
		instance = this;
		

	    
//	    adView.setVisibility(View.INVISIBLE);
	}

    public Cocos2dxGLSurfaceView onCreateView() {
    	Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this);
    	// dots should create stencil buffer
    	glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8);
    	
    	return glSurfaceView;
    }

    static {
        System.loadLibrary("cocos2dcpp");
    }     
}
