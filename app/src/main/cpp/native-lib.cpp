#include <jni.h>
#include <string>

//extern "C" JNIEXPORT jstring JNICALL
//Java_com_example_matrix_MainActivity_stringFromJNI(
//        JNIEnv* env,
//        jobject /* this */) {
//    std::string hello = "Hello from C++, how are you";
//    return env->NewStringUTF(hello.c_str());
//}

#include <jni.h>

extern "C" JNIEXPORT void JNICALL
Java_com_example_matrix_MainActivity_nativeTransposeMatrix(JNIEnv *env, jobject instance,
                                                           jobjectArray matrix_) {
    jsize rows = env->GetArrayLength(matrix_);
    jsize cols = env->GetArrayLength(static_cast<jarray>(env->GetObjectArrayElement(matrix_, 0)));

    jclass intArrayClass;
    jobjectArray transposedMatrix = env->NewObjectArray(cols, intArrayClass, nullptr);

    for (jsize j = 0; j < cols; j++) {
        jintArray newRow = env->NewIntArray(rows);
        for (jsize i = 0; i < rows; i++) {
            jintArray originalRow = static_cast<jintArray>(env->GetObjectArrayElement(matrix_, i));
            jint *element = env->GetIntArrayElements(originalRow, nullptr);
            env->SetIntArrayRegion(newRow, i, 1, &element[j]);
            env->ReleaseIntArrayElements(originalRow, element, 0);
            env->DeleteLocalRef(originalRow);
        }
        env->SetObjectArrayElement(transposedMatrix, j, newRow);
        env->DeleteLocalRef(newRow);
    }

    // Replace each row in the original matrix with the corresponding row from the transposed matrix
    for (jsize i = 0; i < rows; i++) {
        jintArray transposedRow = static_cast<jintArray>(env->GetObjectArrayElement(transposedMatrix, i));
        env->SetObjectArrayElement(matrix_, i, transposedRow);
        env->DeleteLocalRef(transposedRow);
    }

    env->DeleteLocalRef(transposedMatrix);
}