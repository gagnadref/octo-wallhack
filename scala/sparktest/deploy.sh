#!/bin/bash

sbt package
$SPARK_HOME/bin/spark-submit --class SparkTest --master spark://dell:7077 target/scala-2.10/spark-test_2.10-0.0.1.jar
