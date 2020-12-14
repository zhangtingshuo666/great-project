const devicesId = "642900899" // 填写在OneNet上获得的devicesId 形式就是一串数字 例子:9939133
const api_key = "jcK5paqnhWIIrICN6duaYaINx2g=" // 填写在OneNet上的 api-key 例子: VeFI0HZ44Qn5dZO14AuLbWSlSlI=
Page({
  data:{
    ceng3:'',
    num3:''
  },

     /**
   * @description 页面下拉刷新事件
   */
  tap:function(){
   
 this.setData({
   num3:this.data.num3+1
 })
 
   },
  onPullDownRefresh: function () {
    wx.showLoading({
      title: "正在获取"
    })
    this.getDatapoints().then(datapoints => {
      this.update(datapoints)
      wx.hideLoading()
    }).catch((error) => {
      wx.hideLoading()
      console.error(error)
    })
  },

  /**
   * @description 页面加载生命周期
   */
  onLoad: function () {
    console.log(`your deviceId: ${devicesId}, apiKey: ${api_key}`)

    //每隔6s自动获取一次数据进行更新
   /* var that=this;
    const timer = setInterval(() => {
      this.getDatapoints().then(datapoints => {
      console.log(datapoints)
      that.setData({
        ceng3:datapoints.temperature[19].value
      })
      })
    }, 5000)*/

    //获取数据
    var that = this
    wx.request({
      url: "https://api.heclouds.com/devices/642900899/datapoints",   
      header: {
        "api-key": "jcK5paqnhWIIrICN6duaYaINx2g="              
      },
      data: {
        limit: 1
      },
      method: "GET",
      success: function (e) {
        console.log(e.data.data)
        that.setData({
       
          ceng3:e.data.data.datastreams[2].datapoints[0].value,
          num3:e.data.data.datastreams[5].datapoints[0].value,
        })
      }
    });

    wx.showLoading({
      title: '加载中'
    })

    this.getDatapoints().then((datapoints) => {
      wx.hideLoading()
    }).catch((err) => {
      wx.hideLoading()
      console.error(err)
      clearInterval(timer) //首次渲染发生错误时禁止自动刷新
    })
  },

  /**
   * 向OneNet请求当前设备的数据点
   * @returns Promise
   */
  getDatapoints: async function () {
    var that = this;
    return new Promise((resolve, reject) => {
      wx.request({
        url: `https://api.heclouds.com/devices/${devicesId}/datapoints?datastream_id=Temperature,Humidity&limit=20`,
        /**
         * 添加HTTP报文的请求头, 
         * 其中api-key为OneNet的api文档要求我们添加的鉴权秘钥
         * Content-Type的作用是标识请求体的格式, 从api文档中我们读到请求体是json格式的
         * 故content-type属性应设置为application/json
         */
        header: {
          'content-type': 'application/json',
          'api-key': api_key
        },
        success: (res) => {
          
          const status = res.statusCode
          const response = res.data
          if (status !== 200) { // 返回状态码不为200时将Promise置为reject状态
            reject(res.data)
            return ;
          }
          if (response.errno !== 0) { //errno不为零说明可能参数有误, 将Promise置为reject
            reject(response.error)
            return ;
          }

          if (response.data.datastreams.length === 0) {
            reject("当前设备无数据, 请先运行硬件实验")
          }
           //程序可以运行到这里说明请求成功, 将Promise置为resolve状态
           resolve({
            temperature: response.data.datastreams[0].datapoints.reverse(),
            humidity: response.data.datastreams[1].datapoints.reverse()
          })
        },
        fail: (err) => {
          reject(err)
        }
      })
    })
  },
  
   
  //点击上传数据按键将数据回传至云端
  ta:function(){

    wx.request({
      url: 'http://api.heclouds.com/devices/642900899/datapoints',
      method: 'POST',
      header: {
        'api-key': 'jcK5paqnhWIIrICN6duaYaINx2g='
      },
      data: {
        'datastreams': [{
          'id': 'tui',
          'datapoints': [{
            'value': this.data.num3
          }]
        }]
      },
      success: res => {
        console.log(res)
      },
      fail: err => {
        console.log(err)
      }
    })
  }

})
