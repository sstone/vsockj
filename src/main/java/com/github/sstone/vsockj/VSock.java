package com.github.sstone.vsockj;

public class VSock {
    public static native long open();
    public static native long connect(long ctx, int cid, int port);
    public static native long send(long ctx, byte[] message, int offset, int len);
    public static native byte[] receive(long ctx, int len);

    static {
        System.loadLibrary("vsockj-jni");
    }
}
