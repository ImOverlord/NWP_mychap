pipeline {
  agent none

  triggers {
    cron('H * * * *')
  }

  options {
    timestamps()
  }

  stages {
    // Setup phase if we need to implement script or whatever
    //
    // stage('Setup') {
    //   agent {
    //     docker {
    //       image 'epitechcontent/epitest-docker'
    //     }
    //   }
    //   steps {
    //     sh 'chmod +x ./ci/script/*.sh'
    //     sh 'mkdir art'
    //   }
    // }

    stage('Build') {
      agent {
        docker {
          image 'epitechcontent/epitest-docker'
        }
      }
      steps {
        timeout(time: 10) {
          sh 'make fclean'
          sh 'make'
          sh 'make clean'
          sh 'make re'
          sh 'make fclean'
          sh 'make all'
        }
      }
    }

    stage('Tests') {
      agent {
        docker {
          image 'epitechcontent/epitest-docker'
        }
      }
      steps {
        retry(count: 3) {
          timeout(time: 20) {
            sh 'make tests_run'
          }
        }
      }
    }

    stage('Deploy') {
      agent any
      when {
        anyOf {
          branch 'master'
          branch 'edge'
        }
        allOf {
          not {
            changeRequest()
          }
          not {
            triggeredBy('TimerTrigger')
          }
        }
      }
      steps {
        sshagent (credentials: ['epitech-global']) {
          sh "git push git@git.epitech.eu:/thibault-alexandre.faure@epitech.eu/NWP_mychap_2018 --force ${env.BRANCH_NAME}:${env.BRANCH_NAME}"
        }
      }
    }
  }
}