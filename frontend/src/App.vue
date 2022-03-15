<script>
import axios from 'axios'

export default {
  data() {
    return {
      items: [],
      filtered: [],
      loading: true,
      lessons: [],
      // scheduleDay: (new Date()).getDay(),
      scheduleDay: 5,
      weekDays: ['Воскресенье', 'Понедельник', 'Вторник', 'Среда', 'Четверг', 'Пятница', 'Суббота'],
      time: [
        '8:00-8:45',
        '9:00-9:45',
        '10:00-10:45',
        '11:00-11:45',
        '12:00-12:45',
        '13:00-13:45',
        '14:00-14:45',
        '15:00-15:45',
        '16:00-16:45',
      ]
    }
  },

  created() {
    this.fetchData()
  },

  computed: {
    filtered: function (){
      let res = this.items.filter(i => i.week_day === this.weekDays[this.scheduleDay]);
      console.log('f', res);
      return this.items.filter(i => i.week_day === this.weekDays[this.scheduleDay])
    },
  },

  methods: {
    async fetchData() {
      const api = 'http://localhost:8000';
      let {items} = (await axios.get(`${api}/schedule`)).data;

      for (let i of items) {
        i.subjects = JSON.parse(i.subjects);
      }

      this.items = items;
      this.loading = false;
      console.log(items)
    }
  }
}
</script>

<template>
  <main class="main">
    <div class="wrapper">
      <div v-if="loading">
        Загрузка...
      </div>
      <div v-else>
        <div class="nav">
          <button v-on:click="scheduleDay = (scheduleDay - 1) < 0 ? scheduleDay = 6 : scheduleDay -= 1">
            <svg width="24px" height="24px" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg">
              <path fill-rule="evenodd" clip-rule="evenodd"
                    d="M15.6508 4.24075C16.0701 4.60017 16.1187 5.23147 15.7593 5.65079L10.3171 12L15.7593 18.3492C16.1187 18.7685 16.0701 19.3998 15.6508 19.7593C15.2315 20.1187 14.6002 20.0701 14.2407 19.6508L8.24074 12.6508C7.91975 12.2763 7.91975 11.7237 8.24074 11.3492L14.2407 4.34921C14.6002 3.92989 15.2315 3.88132 15.6508 4.24075Z"
                    fill="#575965"/>
            </svg>
          </button>
          <h1>Расписание на {{ weekDays[scheduleDay] }}</h1>
          <button v-on:click="(scheduleDay = (scheduleDay + 1) % 7)">
            <svg width="24px" height="24px" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg">
              <path fill-rule="evenodd" clip-rule="evenodd"
                    d="M8.34923 4.24075C7.9299 4.60017 7.88134 5.23147 8.24076 5.65079L13.6829 12L8.24076 18.3492C7.88134 18.7685 7.9299 19.3998 8.34923 19.7593C8.76855 20.1187 9.39985 20.0701 9.75927 19.6508L15.7593 12.6508C16.0803 12.2763 16.0803 11.7237 15.7593 11.3492L9.75927 4.34921C9.39985 3.92989 8.76855 3.88132 8.34923 4.24075Z"
                    fill="#575965"/>
            </svg>
          </button>
        </div>
        <div class="table-wrapper" v-if="filtered.length > 0">
          <table class="table">
            <thead>
            <tr>
              <th class="head-col">Время</th>
              <th v-for="item of filtered">
                {{ item.class_name }}
              </th>
            </tr>
            </thead>
            <tbody>
            <tr v-for="i in Array(time.length).keys()">
              <td class="head-col">{{ time[i] }}</td>
              <td v-for="j in Array(filtered.length).keys()">
                {{ filtered[j].subjects[i] }}
              </td>
            </tr>
            </tbody>
          </table>
        </div>
        <div v-else>
          <h1>Расписание отсутствует</h1>
        </div>
      </div>
    </div>
  </main>
</template>

<style>
*, *::before, *::after {
  box-sizing: border-box;
}

* {
  margin: 0;
  line-height: calc(1em + 0.5rem);
}

html, body, #app {
  height: 100%;
}

body {
  -webkit-font-smoothing: antialiased;
}

img, picture, video, canvas, svg {
  display: block;
  max-width: 100%;
}

input, button, textarea, select {
  font: inherit;
}

p, h1, h2, h3, h4, h5, h6, th, tr {
  overflow-wrap: break-word;
  color: #505157;
}

#root, #__next {
  isolation: isolate;
}

.main {
  font-family: 'PT Sans', sans-serif;
  display: grid;
  place-items: center;
  height: 100%
}

.wrapper {
  display: flex;
  flex-direction: column;
  align-items: center;
}

th, td {
  text-align: center;
}

h1 {
  margin-bottom: 7px;
  color: #575965;
  text-align: center;
}

.table {
  width: 100%;
  border-spacing: 1em 0.5em;
  background: white;
  border-collapse: separate;
  /*table-layout: fixed;*/
  /*white-space: nowrap;*/
  /*table-layout: fixed;*/
  /*border-collapse: collapse;*/
}

.table-wrapper {
  border-radius: 10px;
  box-shadow: rgba(202, 206, 220, 0.45) 0 4px 10px 1px;
  padding: 10px;
  overflow-x: scroll;
  width: 80%;
  margin: 0 auto;
}

.head-col {
  background: white;
  position: sticky;
  z-index: 1;
  left: -10px;
  padding: 5px 20px;
}

tbody th {
  position: relative;
}

.nav {
  width: 70%;
  margin: 10px auto;
  display: flex;
  align-items: center;
  justify-content: space-between;
}

button {
  background: transparent;
  box-shadow: none;
  border: none;
  cursor: pointer;
}
</style>
