// Copyright 2016 Polyakov Igor

#include <gtest/gtest.h>
#include <cmath>
#include <vector>
#include "include/MatStat.h"


TEST(Polyakov_Igor_MatStatTest, Initialization_Sample_Is_Correct) {
    // Arrange

    int size_sample = 5;
    std::vector<double> sample { 1.0, 3.0, 4.0, -1.0, 0.0 };
    std::vector<double> probabilities { 0.2, 0.1, 0.3333, 0.1, 0.2667 };

    Sample S(sample, probabilities);

    // Act

    int get_size_sample = S.GetSampleSize();
    std::vector<double> get_sample = S.GetSample();
    std::vector<double> get_probabilities = S.GetProbabilities();

    // Assert

    EXPECT_EQ(size_sample, get_size_sample);
    EXPECT_EQ(sample, get_sample);
    EXPECT_EQ(probabilities, get_probabilities);
}

TEST(Polyakov_Igor_MatStatTest, Can_Handle_Incorrect_Sample) {
    // Arrange

    std::vector<double> sample{ 1.0, 3.0, 4.0, 1.0, 0.0 };
    std::vector<double> probabilities{ 0.2, 0.1, 0.3333, 0.1, 0.2667 };

    // Act & Assert

    EXPECT_THROW(Sample(sample, probabilities), IncorrectSample);
}

TEST(Polyakov_Igor_MatStatTest, Can_Handle_Negative_Probability) {
    // Arrange

    std::vector<double> sample{ 1.0, 3.0, 4.0, -1.0, 0.0 };
    std::vector<double> probabilities{ 0.2, 0.1, 0.3333, 0.1, -0.2667 };

    // Act & Assert

    EXPECT_THROW(Sample(sample, probabilities), IncorrectProbabilities);
}

TEST(Polyakov_Igor_MatStatTest, Can_Handle_Summ_Probability_Not_Equal_One) {
    // Arrange

    std::vector<double> sample{ 1.0, 3.0, 4.0, -1.0, 0.0 };
    std::vector<double> probabilities{ 0.2, 0.9, 0.3333, 0.9, 0.9 };

    // Act & Assert

    EXPECT_THROW(Sample(sample, probabilities), IncorrectProbabilities);
}

TEST(Polyakov_Igor_MatStatTest, Can_Handle_Sizes_Sample_And_Prob_Differ) {
    // Arrange

    std::vector<double> sample { 1.0, 3.0, 4.0, -1.0 };
    std::vector<double> probabilities { 0.2, 0.1, 0.3333, 0.1, 0.2667 };

    // Act & Assert

    EXPECT_THROW(Sample(sample, probabilities),
                 IncorrectSizesOfSampleAndProbs);
}

TEST(Polyakov_Igor_MatStatTest, Can_Assign_Sample_With_Other_Size) {
    // Arrange

    std::vector<double> sample_1 { 1.0, 3.0, 4.0, -1.0, 0.0 };
    std::vector<double> probabilities_1 { 0.2, 0.1, 0.3333, 0.1, 0.2667 };

    std::vector<double> sample_2 { 1.0, 3.0, 4.0, -1.0 };
    std::vector<double> probabilities_2 { 0.2, 0.1, 0.3333, 0.3667 };

    Sample S_1(sample_1, probabilities_1);
    Sample S_2(sample_2, probabilities_2);

    // Act

    S_2 = S_1;

    // Assert

    ASSERT_EQ(S_1, S_2);
}

TEST(Polyakov_Igor_MatStatTest, Samples_With_Differ_Size_Are_Inequal) {
    // Arrange

    std::vector<double> sample_1 { 1.0, 3.0, 4.0, -1.0 };
    std::vector<double> probabilities_1 { 0.2, 0.1, 0.3333, 0.3667 };

    std::vector<double> sample_2 { 1.0, 3.0, 4.0, -1.0, 0.0 };
    std::vector<double> probabilities_2 { 0.2, 0.1, 0.3333, 0.1, 0.2667 };

    Sample S_1(sample_1, probabilities_1);
    Sample S_2(sample_2, probabilities_2);

    // Act & Assert

    ASSERT_FALSE(S_1 == S_2);
}

TEST(Polyakov_Igor_MatStatTest, Samples_With_Differ_Prob_Are_Inequal) {
    // Arrange

    std::vector<double> sample_1{ 1.0, 3.0, 4.0, -1.0, 0.0 };
    std::vector<double> probabilities_1{ 0.2, 0.1, 0.3333, 0.1, 0.2667 };

    std::vector<double> sample_2 { 1.0, 3.0, 4.0, -1.0, 0.0 };
    std::vector<double> probabilities_2 { 0.2, 0.1, 0.2667, 0.1, 0.3333 };

    Sample S_1(sample_1, probabilities_1);
    Sample S_2(sample_2, probabilities_2);

    // Act & Assert

    ASSERT_FALSE(S_1 == S_2);
}

TEST(Polyakov_Igor_MatStatTest, Calc_Mathematical_Expectation_Is_Correct) {
    // Arrange

    std::vector<double> sample{ 1.0, 3.0, 4.0, -1.0, 0.0 };
    std::vector<double> probabilities{ 0.2, 0.1, 0.3333, 0.1, 0.2667 };

    Sample S(sample, probabilities);

    // Act

    double mathematical_expectation = S.CalcMathematicalExpectation();

    // Assert

    EXPECT_NEAR(1.7332, mathematical_expectation, SAMPLE_EPSILON);
}

TEST(Polyakov_Igor_MatStatTest, Calculate_Dispersion_Is_Correct) {
    // Arrange

    std::vector<double> sample{ 1.0, 3.0, 4.0, -1.0, 0.0 };
    std::vector<double> probabilities{ 0.2, 0.1, 0.3333, 0.1, 0.2667 };

    Sample S(sample, probabilities);

    // Act

    double dispersion = S.CalcDispersion();

    // Assert

    EXPECT_NEAR(3.5289, dispersion, SAMPLE_EPSILON);
}

TEST(Polyakov_Igor_MatStatTest, Calc_Average_Quadratic_Deviation_Is_Correct) {
    // Arrange

    std::vector<double> sample{ 1.0, 3.0, 4.0, -1.0, 0.0 };
    std::vector<double> probabilities{ 0.2, 0.1, 0.3333, 0.1, 0.2667 };

    Sample S(sample, probabilities);

    // Act

    double average_quadratic_deviation = S.CalcAverageQuadraticDeviation();

    // Assert

    EXPECT_NEAR(1.8785, average_quadratic_deviation, SAMPLE_EPSILON);
}

TEST(Polyakov_Igor_MatStatTest, Calculate_Moment_Is_Correct) {
    // Arrange

    std::vector<double> sample{ 1.0, 3.0, 4.0, -1.0, 0.0 };
    std::vector<double> probabilities{ 0.2, 0.1, 0.3333, 0.1, 0.2667 };

    Sample S(sample, probabilities);

    double relative_point = 1.0;
    int exponent = 3;

    // Act

    double moment = S.CalcMoment(relative_point, exponent);

    // Assert

    EXPECT_NEAR(8.7324, moment, SAMPLE_EPSILON);
}

TEST(Polyakov_Igor_MatStatTest, Calculate_Elementary_Moment_Is_Correct) {
    // Arrange

    std::vector<double> sample{ 1.0, 3.0, 4.0, -1.0, 0.0 };
    std::vector<double> probabilities{ 0.2, 0.1, 0.3333, 0.1, 0.2667 };

    Sample S(sample, probabilities);

    int exponent = 3;

    // Act

    double elementary_moment = S.CalcElementaryMoment(exponent);

    // Assert

    EXPECT_NEAR(24.1312, elementary_moment, SAMPLE_EPSILON);
}

TEST(Polyakov_Igor_MatStatTest, Calculate_Central_Moment_Is_Correct) {
    // Arrange

    std::vector<double> sample{ 1.0, 3.0, 4.0, -1.0, 0.0 };
    std::vector<double> probabilities{ 0.2, 0.1, 0.3333, 0.1, 0.2667 };

    Sample S(sample, probabilities);

    int exponent = 3;

    // Act

    double central_moment = S.CalcCentralMoment(exponent);

    // Assert

    EXPECT_NEAR(0.5762, central_moment, SAMPLE_EPSILON);
}

TEST(Polyakov_Igor_MatStatTest, Dispers_Is_Central_Moment_Of_Two_Exp) {
    // Arrange

    std::vector<double> sample{ 1.0, 3.0, 4.0, -1.0, 0.0 };
    std::vector<double> probabilities{ 0.2, 0.1, 0.3333, 0.1, 0.2667 };

    Sample S(sample, probabilities);

    int exponent = 2;

    // Act

    double dispersion = S.CalcDispersion();
    double central_moment = S.CalcCentralMoment(exponent);

    // Assert

    EXPECT_NEAR(central_moment, dispersion, SAMPLE_EPSILON);
}

TEST(Polyakov_Igor_MatStatTest, Can_Calc_Dispers_Through_Math_Expectation) {
    // Arrange

    std::vector<double> sample{ 1.0, 3.0, 4.0, -1.0, 0.0 };
    std::vector<double> probabilities{ 0.2, 0.1, 0.3333, 0.1, 0.2667 };

    Sample S(sample, probabilities);

    // Act

    double dispersion = S.CalcElementaryMoment(2) -
                        pow(S.CalcMathematicalExpectation(), 2);

    // Assert

    EXPECT_NEAR(3.5289, dispersion, SAMPLE_EPSILON);
}

TEST(Polyakov_Igor_MatStatTest, Dispersion_Of_Constant_Equal_Is_Zero) {
    // Arrange

    std::vector<double> sample { 5.0 };
    std::vector<double> probabilities { 1.0 };

    Sample S(sample, probabilities);

    // Act

    double dispersion = S.CalcDispersion();

    // Assert

    EXPECT_NEAR(0.0, dispersion, SAMPLE_EPSILON);
}

TEST(Polyakov_Igor_MatStatTest, Dispersion_Is_Positive) {
    // Arrange

    std::vector<double> sample { -50.0, -100.0, -60.0, -70.0, 0.0 };
    std::vector<double> probabilities { 0.2, 0.1, 0.3333, 0.1, 0.2667 };

    Sample S(sample, probabilities);

    // Act

    double dispersion = S.CalcDispersion();

    // Assert

    ASSERT_LE(0.0, dispersion);
}

TEST(Polyakov_Igor_MatStatTest, Can_Out_Constant_From_Dispersion) {
    // Arrange

    double a = 2.0;
    double b = 50.5;

    std::vector<double> sample_1{ a * 1.0 + b,
                                  a * 3.0 + b,
                                  a * 4.0 + b,
                                  a * (-1.0) + b,
                                  a * 0.0 + b };

    std::vector<double> sample_2 { 1.0, 3.0, 4.0, -1.0, 0.0 };
    std::vector<double> probabilities { 0.2, 0.1, 0.3333, 0.1, 0.2667 };

    Sample S_1(sample_1, probabilities);
    Sample S_2(sample_2, probabilities);

    // Act

    double dispersion_1 = S_1.CalcDispersion();
    double dispersion_2 = S_2.CalcDispersion();

    // Assert
    // D(a*E + b) = a^2 * D(E)
    EXPECT_NEAR(dispersion_1, pow(a, 2) * dispersion_2, SAMPLE_EPSILON);
}
