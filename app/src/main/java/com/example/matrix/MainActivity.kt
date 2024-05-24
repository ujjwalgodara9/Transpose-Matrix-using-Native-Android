package com.example.matrix

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import java.io.BufferedReader

class MainActivity : AppCompatActivity() {

    private external fun nativeTransposeMatrix(matrix: Array<IntArray>)

    companion object {
        init {
            System.loadLibrary("native-lib")
        }
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        // Read the matrix from the file
        //val matrixFile = assets.open("matrix.txt")
        val matrixFile = assets.open("matrix.txt")
        val lines = matrixFile.bufferedReader().use(BufferedReader::readLines)
        val matrix = Array(100) { IntArray(100) }
        for (i in 0..99) {
            val row = lines[i].split(" ").map { it.toInt() }
            matrix[i] = row.toIntArray()
        }

        // Time the native approach
        val nativeStartTime = System.nanoTime()
        nativeTransposeMatrix(matrix)
        val nativeEndTime = System.nanoTime()
        val nativeTime = nativeEndTime - nativeStartTime
        println("Native time: $nativeTime ns")

        // Time the Kotlin approach
        val kotlinStartTime = System.nanoTime()
        val transposedMatrix = transposeMatrix(matrix)
        val kotlinEndTime = System.nanoTime()
        val kotlinTime = kotlinEndTime - kotlinStartTime
        println("Kotlin time: $kotlinTime ns")
    }

    fun transposeMatrix(matrix: Array<IntArray>): Array<IntArray> {
        val rows = matrix.size
        val cols = matrix[0].size
        val transposedMatrix = Array(cols) { IntArray(rows) }

        for (i in 0 until rows) {
            for (j in 0 until cols) {
                transposedMatrix[j][i] = matrix[i][j]
            }
        }

        return transposedMatrix
    }
}