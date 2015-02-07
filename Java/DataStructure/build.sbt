val projectSetting = Seq(
  version := "1.0",
  organization := "edu.nccu.plsm",
  scalaVersion := (Versions scala),
  javacOptions ++= Seq("-source", Versions java, "-target", Versions java),
  resolvers += "plsm" at "http://www.plsm.cs.nccu.edu.tw/repository/public",
  libraryDependencies += specs2core % "test",
  scalacOptions in Test ++= Seq("-Yrangepos")
)

lazy val specs2core = "org.specs2" %% "specs2-core" % "2.4.15"

lazy val root = (project in file("."))
  .settings(projectSetting: _*)
  .settings(
    name := "lab-train"
  ).aggregate(collection)

lazy val collection = (project in file("collection"))
  .settings(projectSetting: _*)
  .settings(
    name := "collection"
    //libraryDependencies
  )
