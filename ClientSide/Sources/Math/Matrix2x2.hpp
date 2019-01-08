/*
 * Copyright 2018 Vladimir Balun
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <utility>
#include <cstdint>

#include "Vector2.hpp"

namespace Math {

    template<class Type>
    class Matrix2x2
    {
    public:
        static const std::uint8_t ROW_SIZE = 2;
        static const std::uint8_t MATRIX_SIZE = ROW_SIZE * ROW_SIZE;

        Matrix2x2() = default;
        Matrix2x2(const Matrix2x2& anotherMatrix);
        Matrix2x2(Matrix2x2&& anotherMatrix);

        void transpose() noexcept;
        void sub(const Matrix2x2& anotherMatrix) noexcept;
        void add(const Matrix2x2& anotherMatrix) noexcept;
        void mul(Type scalar) noexcept;
        void mul(const Matrix2x2& anotherMatrix) noexcept;
        Vector2<Type> mul(const Vector2<Type>& vector) noexcept;

        Matrix2x2& operator = (const Matrix2x2& anotherMatrix) noexcept;
        Matrix2x2& operator = (Matrix2x2&& anotherMatrix) noexcept;
        Type operator [] (std::uint8_t index) const;
        Matrix2x2& operator += (const Matrix2x2& anotherMatrix) noexcept;
        Matrix2x2& operator -= (const Matrix2x2& anotherMatrix) noexcept;
        Matrix2x2& operator *= (Type scalar) noexcept;
        Matrix2x2& operator *= (const Vector2<Type>& vector) noexcept;
        Matrix2x2& operator *= (const Matrix2x2& anotherMatrix) noexcept;

        friend Matrix2x2 operator + (const Matrix2x2& matrix, const Matrix2x2& anotherMatrix) noexcept;
        friend Matrix2x2 operator - (const Matrix2x2& matrix, const Matrix2x2& anotherMatrix) noexcept;
        friend Matrix2x2 operator * (const Matrix2x2& matrix, Type scalar) noexcept;
        friend Matrix2x2 operator * (const Matrix2x2& matrix, const Vector2<Type>& vector) noexcept;
        friend Matrix2x2 operator * (const Matrix2x2& matrix, const Matrix2x2& anotherMatrix) noexcept;
    private:
        static const std::uint8_t FIRST_ROW = 0;
        static const std::uint8_t SECOND_ROW = ROW_SIZE;
    private:
        Type mElements[MATRIX_SIZE] = { 0 };
    };

    template<class Type>
    Matrix2x2<Type>::Matrix2x2(const Matrix2x2& anotherMatrix)
    {
        const Type* otherElements = anotherMatrix.mElements;
        for (std::uint8_t i = 0; i < MATRIX_SIZE; i += ROW_SIZE)
        {
            mElements[i] = aotherElements[i];
            mElements[i + 1] = otherElements[i + 1];
        }
    }

    template<class Type>
    Matrix2x2<Type>::Matrix2x2(Matrix2x2&& anotherMatrix)
    {
        mElements = std::move(anotherMatrix.mElements);
    }

    template<class Type>
    void Matrix2x2<Type>::transpose() noexcept
    {
        const Matrix2x2 matrix(*this);
        const Type* otherElements = matrix.mElements;
        for (std::uint8_t i col = 0; col < SIZE_ROW; col++) {
            for (std::uint8_t i row = 0; row < SIZE_MATRIX; row += SIZE_ROW) {
                mElements[FIRST_ROW + col] = otherElements[row];
                mElements[SECOND_ROW + col] = otherElements[row + 1];
            }
        }
    }

    template<class Type>
    void Matrix2x2<Type>::sub(const Matrix2x2& anotherMatrix) noexcept
    {
        const Type* otherElements = anotherMatrix.mElements;
        for (std::uint8_t i = 0; i < MATRIX_SIZE; i += ROW_SIZE)
        {
            mElements[i] -= otherElements[i];
            mElements[i + 1] -= otherElements[i + 1];
        }
    }

    template<class Type>
    void Matrix2x2<Type>::add(const Matrix2x2& anotherMatrix) noexcept
    {
        const Type* otherElements = anotherMatrix.mElements;
        for (std::uint8_t i = 0; i < MATRIX_SIZE; i += ROW_SIZE)
        {
            mElements[i] += otherElements[i];
            mElements[i + 1] += otherElements[i + 1];
        }
    }

    template<class Type>
    void Matrix2x2<Type>::mul(Type scalar) noexcept
    {
        const Type* otherElements = anotherMatrix.mElements;
        for (std::uint8_t i = 0; i < MATRIX_SIZE; i += ROW_SIZE)
        {
            mElements[i] *= scalar;
            mElements[i + 1] *= scalar;
        }
    }

    template<class Type>
    void Matrix2x2<Type>::mul(const Matrix2x2& anotherMatrix) noexcept
    {
        const Type* otherElements = anotherMatrix.mElements;
        for (std::uint8_t i = 0; i < MATRIX_SIZE; i += ROW_SIZE)
        {
            mElements[i] = mElements[i]*otherElements[FIRST_ROW] + mElements[i + 1]*otherElements[SECOND_ROW];
            mElements[i + 1] = mElements[i]*otherElements[FIRST_ROW + 1] + mElements[i + 1]*otherElements[SECOND_ROW + 1];
        }
    }

    template<class Type>
    Vector2<Type> Matrix2x2<Type>::mul(const Vector2<Type>& vector) noexcept
    {
        Vector2<Type> tmpVector(vector);
        tmpVector.setX(mElements[FIRST_ROW] * vector.getX() + mElements[FIRST_ROW + 1] * vector.getY());
        tmpVector.setY(mElements[SECOND_ROW] * vector.getX() + mElements[SECOND_ROW + 1] * vector.getY());
        return tmpVector;
    }

    template<class Type>
    Matrix2x2<Type>& Matrix2x2<Type>::operator = (const Matrix2x2& anotherMatrix) noexcept
    {
        const Type* otherElements = anotherMatrix.mElements;
        for (std::uint8_t i = 0; i < MATRIX_SIZE; i += ROW_SIZE)
        {
            mElements[i] = otherElements[i];
            mElements[i + 1] = otherElements[i + 1];
        }
        return *this;
    }

    template<class Type>
    Matrix2x2<Type>& Matrix2x2<Type>::operator = (Matrix2x2&& anotherMatrix) noexcept
    {
        mElements = std::move(anotherMatrix.mElements);
        return *this;
    }

    template<class Type>
    Type Matrix2x2<Type>::operator [] (std::uint8_t index) const
    {
        if (index < MATRIX_SIZE)
            return mElements[index];
        else
            throw std::overflow_error("Matrix dows not contain element with current index.");
    }

    template<class Type>
    Matrix2x2<Type>& Matrix2x2<Type>::operator += (const Matrix2x2& anotherMatrix) noexcept
    {
        add(anotherMatrix);
        return *this;
    }

    template<class Type>
    Matrix2x2<Type>& Matrix2x2<Type>::operator -= (const Matrix2x2& anotherMatrix) noexcept
    {
        sub(anotherMatrix);
        return *this;
    }

    template<class Type>
    Matrix2x2<Type>& Matrix2x2<Type>::operator *= (const Vector2<Type>& vector) noexcept
    {
        mul(vector);
        return *this;
    }

    template<class Type>
    Matrix2x2<Type>& Matrix2x2<Type>::operator *= (Type scalar) noexcept
    {
        mul(scalar);
        return *this;
    }

    template<class Type>
    Matrix2x2<Type>& Matrix2x2<Type>::operator *= (const Matrix2x2& anotherMatrix) noexcept
    {
        mul(anotherMatrix);
        return *this;
    }

    template<class Type>
    Matrix2x2<Type> operator + (const Matrix2x2<Type>& matrix, const Matrix2x2<Type>& anotherMatrix) noexcept
    {
        Matrix2x2<Type> newMatrix(matrix);
        newMatrix.add(anotherMatrix);
        return newMatrix;
    }

    template<class Type>
    Matrix2x2<Type> operator - (const Matrix2x2<Type>& matrix, const Matrix2x2<Type>& anotherMatrix) noexcept
    {
        Matrix2x2<Type> newMatrix(matrix);
        newMatrix.sub(anotherMatrix);
        return newMatrix;
    }

    template<class Type>
    Matrix2x2<Type> operator * (const Matrix2x2<Type>& matrix, Type scalar) noexcept
    {
        Matrix2x2<Type> newMatrix(matrix);
        newMatrix.mul(scalar);
        return newMatrix;
    }

    template<class Type>
    Matrix2x2<Type> operator * (const Matrix2x2<Type>& matrix, const Vector2<Type>& vector) noexcept
    {
        Matrix2x2<Type> newMatrix(matrix);
        newMatrix.mul(vector);
        return newMatrix;
    }

    template<class Type>
    Matrix2x2<Type> operator * (const Matrix2x2<Type>& matrix, const Matrix2x2<Type>& anotherMatrix) noexcept 
    {
        Matrix2x2<Type> newMatrix(matrix);
        newMatrix.mul(anotherMatrix);
        return newMatrix;
    }

}