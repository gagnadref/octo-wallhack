import org.apache.spark.SparkConf
import org.apache.spark.SparkContext
import scala.util.Random

object SparkTest extends App {
  val sparkConf = new SparkConf()
  sparkConf.setAppName("Spark Test")
  val sc = new SparkContext(sparkConf)
  val iter = 10000000
  val res = sc.parallelize(1 to iter).cache().map { i =>
    val x = Math.random()
    val y = Math.random()
    if (x*x + y*y < 1) 1 else 0
  }.reduce(_ + _)*4.0/iter

  def printToFile(f: java.io.File)(op: java.io.PrintWriter => Unit) {
    val p = new java.io.PrintWriter(f)
    try {
      op(p)
      } finally {
        p.close()
      }
  } 

  printToFile(new java.io.File("test.txt")) { p => 
    p.println(res)
  }
}
