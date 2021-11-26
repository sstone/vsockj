plugins {
    java
    application
    `java-library`
    publishing
    `maven-publish`
}

group = "com.github.sstone"
//artifactId = "vsockj"
version = "1.0-SNAPSHOT"

repositories {
    mavenCentral()
}

dependencies {
    testImplementation("org.junit.jupiter:junit-jupiter-api:5.6.0")
    testRuntimeOnly("org.junit.jupiter:junit-jupiter-engine")
}

tasks.getByName<Test>("test") {
    useJUnitPlatform()
}

publishing {
    publications {
        create<MavenPublication>("maven") {
            groupId = "com.github.sstone"
            artifactId = "vsockj"
            version = "1.0-SNAPSHOT"
            from(components["java"])
        }
    }
}

application {
    mainClass.set("com.github.sstone.vsockj.Boot")
}


