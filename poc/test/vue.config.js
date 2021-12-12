// vue.config.js
const HtmlWebpackPlugin = require('html-webpack-plugin')
const HtmlWebpackInlineSourcePlugin = require('html-webpack-inline-source-plugin');
module.exports = {
    css: {
        extract: false,
    },
    configureWebpack: {
      optimization: {
        splitChunks: false
      }
    }
  }