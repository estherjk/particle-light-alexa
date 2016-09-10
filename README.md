# particle-light-alexa

Ask Amazon Alexa to control a light. In this case, the "light" is a NeoPixel ring connected to a Particle Photon. The functions to control the light are exposed through the [Particle Cloud](https://docs.particle.io/reference/firmware/photon/#particle-function-). The Alexa skill then calls the functions using the [JavaScript Particle API](https://docs.particle.io/reference/javascript/#callfunction).

*Note: You don't need an Amazon Alexa device to get started... although it's certainly more fun if you have an Echo, Tap, or Dot! You can use [Echosim.io](https://echosim.io/), which is a web-based Alexa skill testing tool.*

## Supplies

* [Particle Photon](https://store.particle.io/)
* [NeoPixel Ring - 16 x 5050 RGBW LEDs](https://www.adafruit.com/products/2856)
* Breadboard
* Jumper wires

## Setting up Particle

### Hardware configuration

Go through the [Particle Photon Getting Started Guide](https://docs.particle.io/guide/getting-started/intro/photon/) to get your Photon up and running. Then, wire up the board.

Here's a picture of the circuit:

![Circuit](https://raw.githubusercontent.com/drejkim/particle-light-alexa/master/img/circuit.jpg)

And, here's a schematic that makes the wiring a bit clearer:

![Schematic](https://raw.githubusercontent.com/drejkim/particle-light-alexa/master/img/particle-light-alexa_bb.png)

To make it easier to wire up the NeoPixel ring, I used a second breadboard to connect **V+**, **Data In**, and **GND**.

### Using the Particle Dev IDE

* Download the [Particle Dev IDE](https://www.particle.io/dev) and follow the [instructions](https://docs.particle.io/guide/tools-and-features/dev/) on how to log into your account and select your device.
* Open `ino/light.ino` in the IDE.
* Send the code to the board
  * Select the **Compile** button. If it's compiled successfully, the status bar on the bottom should say, "Success!"
  * Send the code to the board by selecting the **Flash** button. Again, if it's successful, the status bar should say, "Success!"

## Setting up Amazon Alexa Services

### AWS Lambda Setup

1. Navigate to `particle-light-alexa/alexa/src`
* Type `npm install` to install the required Node.js packages
* Zip up all the files in the `src` folder&mdash;including `node_modules`&mdash; but not the `src` folder itself!
* Go to your [AWS Console](https://aws.amazon.com/) and navigate to AWS Lambda
* Make sure the region is **US East (N. Virginia)**
* If you have no Lambda functions yet, click **Get Started Now**; otherwise, click **Create a Lambda Function**
* Skip the step **Select blueprint**
* In **Configure triggers**, select **Alexa Skills Kit** from the gray dotted box, then click **Next**
* In **Configure function**:
  * Name: ParticleLight
  * Runtime: Node.js 4.3
  * Code entry type: Upload a .ZIP file
    * Select the .ZIP file created in step 3
  * Handler: index.Handler
  * Role: Choose an existing role
  * Existing role: lambda_basic_execution
  * Memory (MB): 128
  * Timeout: 0 min 10 sec
    * I increased the default from 3 sec to 10 sec to give enough time for the request to process
  * VPC: No VPC
* Then, create the function
* Make note of ARN for the new Lambda function, which is on the upper-right of the function page... you'll need this when setting up the Alexa skill

### Alexa Skills Setup

* Go to your [Amazon Developer Dashboard](https://developer.amazon.com) and select **Alexa**
* Select **Get Started** with Alexa Skills Kit
* Select **Add a New Skill**
* In **Skill Information**:
  * Skill Type: Custom Interaction Model
  * Name: ParticleLight
  * Invocation Name: particle light
  * Audio Player: No
* In **Interaction Model**:
  * Intent Schema: Copy and paste the content from `particle-light-alexa/alexa/speechAssets/IntentSchema.json`
  * Custom Slot Types: Select **Add Slot Type**
    * Enter Type: LIST_OF_COLORS
    * Enter Values: Copy and paste the content from `particle-light-alexa/alexa/speechAssets/LIST_OF_COLORS.txt`
  * Custom Slot Types: Select **Add Slot Type**
    * Enter Type: LIST_OF_STATES
    * Enter Values: Copy and paste the content from `particle-light-alexa/alexa/speechAssets/LIST_OF_STATES.txt`
  * Sample Utterances: Copy and paste the content from `particle-light-alexa/alexa/speechAssets/SampleUtterances.txt`
* In **Configuration**:
  * Endpoint: Lambda ARN
    * Copy and paste the ARN from the last step of **AWS Lambda Setup**
  * Account Linking: No

### Using Echosim.io

* Go to [Echosim.io](https://echosim.io/)
* Try out either one of these commands:
  * *Alexa, open particle light*
  * *Alexa, ask particle light to turn {on | off}*
  * *Alexa, ask particle light to change color to {red | green | blue | white}*
  * *Alexa, ask particle light to set brightness level to {x}, where x is 0-255*

And, Alexa should respond accordingly! You can also try this out with your own Alexa-enabled device.
