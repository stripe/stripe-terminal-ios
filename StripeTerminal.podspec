Pod::Spec.new do |s|
  s.name                           = 'StripeTerminal'
  s.version                        = '1.0-b1'
  s.summary                        = 'The programmable point of sale.'
  s.homepage                       = 'https://stripe.com/terminal'
  s.authors                        = { 'Stripe' => 'support+github@stripe.com' }
  s.source                         = { :git => 'https://github.com/stripe/stripe-terminal-ios.git', :tag => "v1.0-b1" }
  s.frameworks                     = 'Foundation', 'Security', 'CoreBluetooth', 'CoreLocation', 'CoreAudio', 'MediaPlayer', 'ExternalAccessory'
  s.requires_arc                   = true
  s.platform                       = :ios
  s.ios.deployment_target          = '10.0'
  s.source                         = { :http => 'https://github.com/stripe/stripe-terminal-ios/releases/download/v1.0-b1/StripeTerminal.framework.zip' }
  s.ios.vendored_frameworks        = 'StripeTerminal.framework'
  s.license      = { :type => 'MIT', :text => <<-LICENSE
    The MIT License

    Copyright (c) 2011- Stripe, Inc. (https://stripe.com)

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.
    LICENSE
  }
end
