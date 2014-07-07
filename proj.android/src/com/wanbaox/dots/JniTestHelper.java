package com.wanbaox.dots;

import android.app.Activity;
import android.content.Intent;
import android.net.Uri;

/**
author:alexzhou 
email :zhoujiangbohai@163.com
date  :2012-12-14
 **/

public class JniTestHelper {
	
    public JniTestHelper(Activity activity) {
		super();
	}

    public static int addBanner(int a, int b)
    {
    	
    	dots.sHandler.sendEmptyMessage(dots.S_HANDLER_SHOW_BANNER);
    	
    	
    	return 1;
    }

    public static int deleteBanner(int a, int b)
    {

    	dots.sHandler.sendEmptyMessage(dots.S_HANDLER_DELETE_BANNER);
    	

    	return 1;
    }
    
	public static int rate(int a, int b)
    {

		dots.sHandler.sendEmptyMessage(dots.S_HANDLER_RATE);
    	return 1;
    }

	public static int gotoMyQQ(int a, int b)
    {

		dots.sHandler.sendEmptyMessage(dots.S_HANDLER_GOTOQQ);
    	return 1;
    }
}

