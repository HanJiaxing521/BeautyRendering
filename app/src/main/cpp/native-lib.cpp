
#include "RenderTexture.h"
#include "RenderFace.h"

static CRenderTexture renderTexOem;
static CRenderFace renderFace;

int gWidth, gHeight, gInputTexture;

bool setupGraphics(int w, int h, int tex) {
    printGLString("Version", GL_VERSION);
    printGLString("Vendor", GL_VENDOR);
    printGLString("Renderer", GL_RENDERER);
    printGLString("Extensions", GL_EXTENSIONS);

    LOGI("setupGraphics(%d, %d, %d)", w, h, tex);
    gWidth = w;
    gHeight = h;
    gInputTexture = tex;

    glViewport(0, 0, w, h);
    checkGlError("glViewport");
    return true;
}

void renderFrame(float *matrix) {
    renderTexOem.Rendering(gInputTexture, matrix);
}

void renderFaceRects(float *matrix, int pointsNum) {

    renderFace.Rendering(matrix, pointsNum);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_wwm_BeautyRendering_NativeJNILib_init(JNIEnv *env, jclass clazz, jint width,
                                                 jint height, jint tex) {
    setupGraphics(width, height, tex);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_wwm_BeautyRendering_NativeJNILib_step(JNIEnv *env, jclass clazz, jfloatArray matrixValues) {
    jfloat* valuesjf = env->GetFloatArrayElements(matrixValues, 0);
    float* valuesf = valuesjf;
    renderFrame(valuesf);
}extern "C"
JNIEXPORT void JNICALL
Java_com_wwm_BeautyRendering_NativeJNILib_drawFaceRects(JNIEnv *env, jclass clazz,
                                                          jfloatArray face_points, int pointsNum) {
    jfloat* valuesjf = env->GetFloatArrayElements(face_points, 0);
    float* valuesf = valuesjf;
    renderFaceRects(valuesf, pointsNum);
}