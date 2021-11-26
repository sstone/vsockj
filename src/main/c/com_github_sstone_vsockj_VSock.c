#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <linux/vm_sockets.h>
#include <time.h>
#include <errno.h>
#include <jni.h>

/*
 * Class:     com_github_sstone_vsockj_VSock
 * Method:    open
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_com_github_sstone_vsockj_VSock_open
  (JNIEnv *penv, jclass clazz)
{
    return socket(AF_VSOCK, SOCK_STREAM, 0);
}

/*
 * Class:     com_github_sstone_vsockj_VSock
 * Method:    connect
 * Signature: (JII)J
 */
JNIEXPORT jlong JNICALL Java_com_github_sstone_vsockj_VSock_connect
  (JNIEnv *penv, jclass clazz, jlong jctx, jint jcid, jint jport)
{
    struct sockaddr_vm addr;
    memset(&addr, 0, sizeof(struct sockaddr_vm));
    addr.svm_family = AF_VSOCK;
    addr.svm_port = jport;
    addr.svm_cid = jcid;
    return connect(jctx, &addr, sizeof(struct sockaddr_vm));
}

/*
 * Class:     com_github_sstone_vsockj_VSock
 * Method:    send
 * Signature: (J[BII)J
 */
JNIEXPORT jlong JNICALL Java_com_github_sstone_vsockj_VSock_send
  (JNIEnv *penv, jclass clazz, jlong jctx, jbyteArray jbuffer, jint joffset, jint jlen)
{
    jbyte* buffer;
    int result;

    buffer = (*penv)->GetByteArrayElements(penv, jbuffer, 0);
    result = send(jctx, buffer + joffset, jlen, 0);
    (*penv)->ReleaseByteArrayElements(penv, jbuffer, buffer, 0);
    return result;
}

/*
 * Class:     com_github_sstone_vsockj_VSock
 * Method:    receive
 * Signature: (JI)[B
 */
JNIEXPORT jbyteArray JNICALL Java_com_github_sstone_vsockj_VSock_receive
  (JNIEnv *penv, jclass clazz, jlong jctx, jint jlen)
{
    unsigned char buffer[2048];
    jbyteArray jreceived = 0;
    jbyte* receivedBytes = 0;
    int result = recv(jctx, buffer, jlen, MSG_WAITALL);
    if (result > 0) {
         jreceived = (*penv)->NewByteArray(penv, result);
         receivedBytes = (*penv)->GetByteArrayElements(penv, jreceived, 0);
         memcpy(receivedBytes, buffer, result);
         (*penv)->ReleaseByteArrayElements(penv, jreceived, receivedBytes, 0);
    }
    return jreceived;
}

